#include <Network_QT.h>
#pragma execution_character_set("utf-8")

Network_QT* Network_QT::network_QT = nullptr;

	/**
 	* @description: Initializer of Network class, should be CALL ONLY ONCE in the beginning of program
	* @return success initing? False when port unavaliable
	*/
bool Network_QT::networkInit() {
	getInstance();
	stopFlag = false;
	listener = new QTcpServer();
	if (!listener->listen(QHostAddress::Any, Setting::getSetting()->getListenPort())) {
		return false;
	}
	QObject::connect(listener, &QTcpServer::newConnection, this, &Network_QT::ConnectHandler);
	//open listen port
	return true;
}

/**
 * @description: Handler of new Call
 */
void Network_QT::ConnectHandler() {
	QTcpSocket* s = this->listener->nextPendingConnection();//get the new socket

	{//wait for 3s of the first message
		time_t call = time(nullptr);
		while (!s->canReadLine()) {
			if (time(nullptr) - call > 3) {
				s->close();
				return;
			}
		}
	}
	if (s->readLine() != "1919810") {//the "ping" should be 1919810
		s->close();
		return;
	}
	s->write("114514");//Pong!

	{//wait for 3s of the second(caller info) message
		time_t call = time(nullptr);
		while (!s->canReadLine()) {
			if (time(nullptr) - call > 3) {
				s->close();
				return;
			}
		}	
	}

    std::string temp = s->readLine().toStdString();
	json callerInfo;
	try {
		callerInfo = json::parse(temp);
		//TODO: Check Black lsit
	}
	catch (int e) {
		s->close();
		return;
	}

	//Accept?
	AcceptCall* acceptThis = new AcceptCall();
	QPixmap tempPix;
	tempPix.loadFromData(QByteArray::fromBase64(callerInfo["ID"]["profile_photo"].get < std::string >().c_str() ));
	acceptThis->setBasicInfo(callerInfo["ID"]["name"], tempPix);
	acceptThis->show();
	if (acceptThis->exec() != (int)QDialog::Accepted); {
		s->close();
		return;
	}

	//Process and send indetity information
	json sendTemp;
	sendTemp["ID"]["Accept"] = true;
	sendTemp["ID"]["name"] = Setting::getSetting()->getName();
	sendTemp["ID"]["profile_photo"] = Mat2Base64(Setting::getSetting()->getProfile(), "jpg");//?
	sendTemp["data"]["model_id"] = Setting::getSetting()->getModelID();
	sendTemp["data"]["session_id"] = GenerateGuid();
	s->write(sendTemp.dump().c_str(), sendTemp.dump().length());

	//Prepare local motion object
	MotionObject* motion = new MotionObject(sendTemp["data"]["session_id"]);
	Network_QT::getInstance()->getDisplayObjects()->push_back(motion);
	motion->setProfileByBase64(callerInfo["ID"]["profile_photo"]);
	if (callerInfo["ID"]["name"].is_string())
		motion->name = callerInfo["ID"]["name"].get<std::string>();
	else
		motion->name = "UNKNOW";

	//Send the first motion pack
	json sendJson;
	sendJson["ID"]["session_id"] = sendTemp["data"]["session_id"];
	//sendJson["ID"]["send_time"] = Necessary?
	sendJson["data"] = *Network_QT::getInstance()->getSendJson();
	s->write(sendTemp.dump().c_str(), sendTemp.dump().length());

/*
* Create a new call object and Thread
* record thrie address
* start the thread and give it to the new thread	
*/
	QThread* newCallThd = new QThread(this);
	CallObj* newCall = new CallObj(motion, s);
	Network_QT::getInstance()->calls.push_back(newCallThd);
	Network_QT::getInstance()->callObjs.push_back(newCall);
	newCallThd->start();
	newCall->moveToThread(newCallThd);
	

	//TODO: Some finishing work
	//motion->alive = false;
}


/**
 * @description: update the send data
 * @param {json} ***"data"*** part of the send object aka "motion data"
 * @return: 
 */
void Network_QT::updateMotion(json& motion)
{
	//qDebug() << QString::fromStdString(motion.dump(1));
	this->sendObject.erase("data");
	this->sendObject["data"] = motion;
	//qDebug() << QString::fromStdString(this->sendObject.dump(1));
}

std::vector<MotionObject*>* Network_QT::getDisplayObjects()
{
	return &this->displayObjects;
}

json* Network_QT::getSendJson()
{
	return &sendObject;
}

void Network_QT::call(std::string ip, int port){
	QTcpSocket* caller = new QTcpSocket();
	caller->connectToHost(QString::fromStdString(ip), port);

	{//wait for 3s of connect
		time_t call = time(nullptr);
		while (caller->state() != QTcpSocket::ConnectedState) {
			if (time(nullptr) - call > 3) {
				caller->close();
				//TODO: window
				return;
			}
		}	
	}

	caller->write("1919810");//Ping!

	{
		time_t call = time(nullptr);
		while (!caller->canReadLine()) {
			if (time(nullptr) - call > 3)
				caller->close();
                throw std::runtime_error("NO_RESPONSE");
		}
	}

	if (caller->readLine() != "114514") {//Pong?
		caller->close();
        throw std::runtime_error("NO_RESPONSE");
	}

//Prepare info
	json exchange;
	exchange["ID"]["name"] = Setting::getSetting()->getName();
	exchange["ID"]["name"] = Mat2Base64(Setting::getSetting()->getProfile(), Setting::getSetting()->getProfileType());

	if (getHostMacAddress()!="")
		exchange["ID"]["MAC"] = getHostMacAddress();
	else
		exchange["ID"]["MAC"] = "UNKNOWN";

	exchange["data"]["model_id"] = Setting::getSetting()->getModelID();
	caller->write(exchange.dump().c_str(),exchange.dump().length());

	{
		time_t call = time(nullptr);
		while (!caller->canReadLine()) {
			if (time(nullptr) - call > 15) //15s Timeout for accept
                throw std::runtime_error("NOT_ACCEPTING");
		}
	}

	json info = json::parse(caller->readLine());
	if (info["ID"]["Accept"]) {
		MotionObject* thisCall = new MotionObject(info["data"]["session_id"]);
		thisCall->setProfileByBase64(info["ID"]["profile_photo"]);
		if (info["ID"]["name"].is_string())
			thisCall->name = info["ID"]["name"].get<std::string>();
		else
			thisCall->name = "UNKNOW";

		Network_QT::getInstance()->getDisplayObjects()->push_back(thisCall);
		CallObj* newCallObj = new CallObj(thisCall, caller);
		QThread* newCallThd = new QThread();
		newCallThd->start();
		newCallObj->moveToThread(newCallThd);
		Network_QT::getInstance()->calls.push_back(newCallThd);
		Network_QT::getInstance()->callObjs.push_back(newCallObj);
	}else{
		caller->close();
	}
}


/**
 * @description: Wrapper of call,
 * @param {string} target host, form e.g. 127.0.0.1:8080 
 * @return: 
 */
void Network_QT::call(std::string target){//IPv4 Only

	qDebug() << "Calling:"<<" " << QString::fromStdString(target);
	if (target.find_first_of(':') == std::string::npos) {
		if (target.find((std::string)"：") == std::string::npos) {
            throw std::runtime_error("BAD_ADDRESS");
		}
		else
		{
			target[target.find_first_of((std::string)"：")] = ':';
		}
	}
	try {
		call(target.substr(target.find_first_of(':')), std::stoi(target.substr(target.find_first_of(':') + 1, target.length() - target.find_first_of(':') - 1)));
	}
	catch (std::string e) {
        throw std::runtime_error("BAD_ADDRESS");
		
	}
}

Network_QT::Network_QT() {
	stopFlag = false;
	listener = nullptr;
	sendObject["ID"];
	sendObject["data"];

}
Network_QT::~Network_QT() {
	delete listener;
	for (QThread* thd : calls) {
		delete thd;
	}
	for (CallObj* obj : callObjs) {
		delete obj;
	}
	for (MotionObject* obj : displayObjects) {
		delete obj;
	}
}

std::string GenerateGuid() {
	return QUuid::createUuid().toString().toStdString();
}

CallObj::CallObj(MotionObject* motion, QTcpSocket* s) {
	this->motion = motion;
	this->s = s;
	sendJson["ID"]["session_id"] = motion->getSessionID();
	QObject::connect(s, &QTcpSocket::readyRead, this, &CallObj::writeObject);
	QObject::connect(FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection, this, &CallObj::sendObject);
	Audio::getInstance()->audioStart();
}
CallObj::~CallObj() {
	delete s;
}
