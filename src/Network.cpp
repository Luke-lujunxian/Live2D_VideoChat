#include "Network.h"
#include "Setting.h"
#include <Socket.h>
#include "Base64.h"

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
}

//Thread funtions End

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




