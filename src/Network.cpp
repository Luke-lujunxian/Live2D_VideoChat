#include "Network.h"
#include "Setting.h"
#include <Socket.h>
#include "Base64.h"
#include < helper.h>

using namespace std;

//Thread funtions
void callHandleFun(Socket* s) {

	//varification
	if (s->ReceiveLine() != "1919810") {
		s->Close();
		return;
	}
	std::string temp = "";
	while (temp == "") {
		temp = s->ReceiveLine();
	}

	json callerInfo;
	try{
		callerInfo = json::parse(temp);
		//TODO: Check Black lsit
	}
	catch (int e) {
		s->Close();
		return;
	}

	//TODO: Accept?
	
	json sendTemp;
	sendTemp["ID"]["Accept"] = true;
	sendTemp["ID"]["name"] = Setting::getSetting()->getName();
	sendTemp["ID"]["profile_photo"] = Mat2Base64(Setting::getSetting()->getProfile(), "jpg");//?
	sendTemp["data"]["model_id"] = Setting::getSetting()->getModelID();
	sendTemp["data"]["session_id"] = GenerateGuid();
	s->SendLine(sendTemp.dump());

	MotionObject* motion = new MotionObject(sendTemp["data"]["session_id"]);
	Network::getInstance()->getDisplayObjects()->push_back(motion);
	motion->setProfileByBase64(callerInfo["ID"]["profile_photo"]);
	motion->name = (std::string)callerInfo["ID"]["name"];

	json sendJson;
	sendJson["ID"]["session_id"] = sendTemp["data"]["session_id"];
	//sendJson["ID"]["send_time"] = Necessary?
	sendJson["data"] = *Network::getInstance()->getSendJson();
	s->SendLine(sendJson.dump());

	clock_t sendTime = clock();
	while (!Network::getInstance()->shouldStop())
	{
		motion->writeObject(s->ReceiveLine());
		if (clock() - sendTime > 1000/30) {//Send in 30 FPS
			s->SendLine(Network::getInstance()->getSendJson()->dump());
			sendTime = clock();
		}
	}
	
	//TODO: Some finishing work
	motion->alive = false;
}

void listenerfun() {
	Setting* setting = Setting::getSetting();
	SocketServer* listener;
	vector<thread> calls = vector<thread>(5);
	try {
		listener = new SocketServer(setting->getListenPort(), setting->getMaximumListenQueue(), NonBlockingSocket);
	}
	catch (int e) {
		if (e == WSAEADDRINUSE)
			throw "Address already in use";
		// And many more https://docs.microsoft.com/zh-cn/windows/win32/winsock/windows-sockets-error-codes-2

		return;
	}
	
	if (true/*p2p mode*/) {
		while (!Network::getInstance()->shouldStop()) {
				Socket* call = listener->Accept();
				if (call == 0)//No incoming connection
					continue;
				Network::getInstance();
				calls.push_back(thread(callHandleFun, call));
			}
	}
	
	//TODO: Some finishing work
	delete listener;
}

void callerfun(Socket* s,MotionObject* motionObj) {
	clock_t sendTime = clock();
	while (!Network::getInstance()->shouldStop())
	{
		motionObj->writeObject(s->ReceiveLine());
		if (clock() - sendTime > 1000 / 30) {//Send in 30 FPS
			s->SendLine(Network::getInstance()->getSendJson()->dump());
			sendTime = clock();
		}
	}
	//Some finish
}

//Thread funtions End

void Network::call(string target)
{
	if(target.find_first_of(':') == string::npos) {
		if (target.find_first_of('��') == string::npos) {
			throw "BAD_ADDRESS";
		}
		else
		{
			target[target.find_first_of('��')] = ':';
		}
	}
	try {
		call(target.substr(target.find_first_of(':')), stoi(target.substr(target.find_first_of(':') + 1, target.length() - target.find_first_of(':') - 1)));
	}
	catch (string e) {
		throw "BAD_ADDRESS";
	}
}

void Network::call(string ip, int port)
{
	SocketClient* caller = new SocketClient(ip, port);
	caller->SendLine("1919810");
	if (caller->ReceiveLine() != "114514") {
		caller->Close();
		throw "NO_RESPONSE";
	}

	json exchange;
	exchange["ID"]["name"] = Setting::getSetting()->getName();
	exchange["ID"]["name"] = Mat2Base64(Setting::getSetting()->getProfile(), Setting::getSetting()->getProfileType());

	std::string temp = "";
	if (GetMacByGetAdaptersInfo(temp))
		exchange["ID"]["MAC"] = temp;
	else
		exchange["ID"]["MAC"] = "UNKNOWN";

	exchange["data"]["model_id"] = Setting::getSetting()->getModelID();
	caller->SendLine(exchange.dump());
	json info = json::parse(caller->ReceiveLine());

	MotionObject* thisCall = new MotionObject(info["data"]["session_id"]);
	thisCall->setProfileByBase64(info["ID"]["profile_photo"]);
	thisCall->name = (std::string)info["ID"]["name"];

	thread callThd = thread(callerfun, &caller,thisCall);
	Network::getInstance()->getDisplayObjects()->push_back(thisCall);
	
	
}

Network::Network() {
	stopFlag = false;
}

void Network::networkInit() {
	getInstance();
	stopFlag = false;
	listener = thread(listenerfun);//open listen port
}

void Network::updateMotion(json& motion)
{
	this->sendObject = motion;
}

std::vector<MotionObject*>* Network::getDisplayObjects()
{
	return &this->displayObjects;
}

json* Network::getSendJson()
{
	return &sendObject;
}




