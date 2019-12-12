#include <Network_QT.h>
Network_QT* Network_QT::network_QT = nullptr;

bool Network_QT::networkInit() {
	getInstance();
	stopFlag = false;
	listener = new QTcpServer();
	if (!listener->listen(QHostAddress::Any, Setting::getSetting()->getListenPort())) {
		return false;
	}
	QObject::connect(listener, &QTcpServer::newConnection, this, &Network_QT::ConnectHandler);
	//open listen port
}

void Network_QT::ConnectHandler() {
	QTcpSocket* s = this->listener->nextPendingConnection();

	while (!s->canReadLine()) {

	}
	if (s->readLine() != "1919810") {
		s->close();
		return;
	}
	std::string temp = "";
	while (temp == "") {
		temp = s->readLine();
	}

	json callerInfo;
	try {
		callerInfo = json::parse(temp);
		//TODO: Check Black lsit
	}
	catch (int e) {
		s->close();
		return;
	}

	//TODO: Accept?

	json sendTemp;
	sendTemp["ID"]["Accept"] = true;
	sendTemp["ID"]["name"] = Setting::getSetting()->getName();
	sendTemp["ID"]["profile_photo"] = Mat2Base64(Setting::getSetting()->getProfile(), "jpg");//?
	sendTemp["data"]["model_id"] = Setting::getSetting()->getModelID();
	sendTemp["data"]["session_id"] = GenerateGuid();
	s->write(sendTemp.dump().c_str(), sendTemp.dump().length());

	MotionObject* motion = new MotionObject(sendTemp["data"]["session_id"]);
	Network_QT::getInstance()->getDisplayObjects()->push_back(motion);
	motion->setProfileByBase64(callerInfo["ID"]["profile_photo"]);
	if (callerInfo["ID"]["name"].is_string())
		motion->name = callerInfo["ID"]["name"].get<std::string>();
	else
		motion->name = "UNKNOW";

	json sendJson;
	sendJson["ID"]["session_id"] = sendTemp["data"]["session_id"];
	//sendJson["ID"]["send_time"] = Necessary?
	sendJson["data"] = *Network_QT::getInstance()->getSendJson();
	s->write(sendTemp.dump().c_str(), sendTemp.dump().length());

	QThread* newCallThd = new QThread(this);
	CallObj* newCall = new CallObj(motion, s);
	Network_QT::getInstance()->calls.push_back(newCallThd);
	Network_QT::getInstance()->callObjs.push_back(newCall);
	newCallThd->start();
	newCall->moveToThread(newCallThd);
	

	//TODO: Some finishing work
	motion->alive = false;
}

void Network_QT::updateMotion(json& motion)
{
	this->sendObject.erase("data");
	this->sendObject.emplace("data", motion);
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
	caller->write("1919810");
	if (caller->readLine() != "114514") {
		caller->close();
		throw "NO_RESPONSE";
	}

	json exchange;
	exchange["ID"]["name"] = Setting::getSetting()->getName();
	exchange["ID"]["name"] = Mat2Base64(Setting::getSetting()->getProfile(), Setting::getSetting()->getProfileType());

	if (getHostMacAddress()!="")
		exchange["ID"]["MAC"] = getHostMacAddress();
	else
		exchange["ID"]["MAC"] = "UNKNOWN";

	exchange["data"]["model_id"] = Setting::getSetting()->getModelID();
	caller->write(exchange.dump().c_str(),exchange.dump().length());
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
	}
}


void Network_QT::call(std::string target){//IPv4 Only
	if (target.find_first_of(':') == std::string::npos) {
		if (target.find_first_of('£º') == std::string::npos) {
			throw "BAD_ADDRESS";
		}
		else
		{
			target[target.find_first_of('£º')] = ':';
		}
	}
	try {
		call(target.substr(target.find_first_of(':')), std::stoi(target.substr(target.find_first_of(':') + 1, target.length() - target.find_first_of(':') - 1)));
	}
	catch (std::string e) {
		throw "BAD_ADDRESS";
	}
}

Network_QT::Network_QT() {
	stopFlag = false;
	listener = nullptr;
	sendObject["ID"];
	sendObject["data"];

}

std::string GenerateGuid() {
	return QUuid::createUuid().toString().toStdString();
}

CallObj::CallObj(MotionObject* motion, QTcpSocket* s) {
	this->motion = motion;
	this->s = s;
	QObject::connect(s, &QTcpSocket::readyRead, this, &CallObj::writeObject);
	QObject::connect(FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection, this, &CallObj::sendObject);
	Audio::getInstance()->audioStart();
}