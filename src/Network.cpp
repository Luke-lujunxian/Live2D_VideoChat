#include "Network.h"
#include "Setting.h"
#include <Socket.h>

Network::Network() {

}

void Network::networkInit() {
	getInstance();
	stopFlag = false;
	listener = thread(listenerfun);//open listen port
}

void Network::updateMotion(json motion)
{
	this->sendObject = motion;
}

vector<json>* Network::getMotion()
{
	return &this->displayObjects;
}

Network* Network::getInstance()
{
	if (network == nullptr)
		Network::network = new Network();
	return network;
}



//Thread funtions
void callHandleFun(Socket* s) {

	if (s->ReceiveLine() != "1919810") {
		s->Close();
		return;
	}
	while (!Network::getInstance()->shouldStop())
	{
		
		
	}
	//TODO: Some finishing work

}

void listenerfun() {
	Setting* setting = Setting::getSetting();
	SocketServer* listener;
	vector<thread> calls = vector<thread>(5);
	try {
		listener = new SocketServer(setting->getListenPort(), setting->getMaximumListenQueue(),NonBlockingSocket);
	}
	catch (string e) {
		if (e == "INVALID_SOCKET")
			throw "OPEN_LISTEN_PORT_FAIL";

		return;
	}

	while (!Network::getInstance()->shouldStop()) {
		Socket* call = listener->Accept();
		if (call == 0)//No incoming connection
			continue;
		calls.push_back(thread(callHandleFun,call));
	}
	//TODO: Some finishing work
}
