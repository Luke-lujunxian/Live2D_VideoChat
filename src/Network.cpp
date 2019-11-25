#include "Network.h"
#include "Setting.h"
#include <Socket.h>

using namespace std;
//Thread funtions
void callHandleFun(Socket* s) {

	//varification
	if (s->ReceiveLine() != "1919810") {
		s->Close();
		return;
	}

	/*
	*
	*TODO:
	*Info Exchange
	*
	*/

	MotionObject* motion = new MotionObject();
	Network::getInstance()->getDisplayObjects()->push_back(motion);


	while (!Network::getInstance()->shouldStop())
	{
		motion->writeObject(s->ReceiveLine());
		s->SendLine(Network::getInstance()->getSendJson()->dump());
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




