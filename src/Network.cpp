#include "Network.h"
#include "Setting.h"
#include <Socket.h>


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
		listener = new SocketServer(setting->getListenPort(), setting->getMaximumListenQueue(), NonBlockingSocket);
	}
	catch (int e) {
		if (e == WSAEADDRINUSE)
			throw "Address already in use";
		// And many more https://docs.microsoft.com/zh-cn/windows/win32/winsock/windows-sockets-error-codes-2

		return;
	}

	while (!Network::getInstance()->shouldStop()) {
		Socket* call = listener->Accept();
		if (call == 0)//No incoming connection
			continue;
		calls.push_back(thread(callHandleFun, call));
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

void Network::updateMotion(json motion)
{
	this->sendObject = motion;
}

vector<json>* Network::getMotion()
{
	return &this->displayObjects;
}



