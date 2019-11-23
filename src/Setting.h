#pragma once
/*
A single instance class to store and access global settings.



*/

class Setting {

public:
	static Setting* getSetting() {
		if(inited)
			return setting;
		return nullptr;
	}

	short const getListenPort() {
		return this->listenPort;
	}

	short const getTranmitPort() {
		return this->callPort;
	}

	short const getMaximumListenQueue() {
		return this->maximumListenQueue;
	}

private:
	Setting();
	Setting(Setting&);
	static bool inited;
	short listenPort;
	short callPort;
	short maximumListenQueue;
	static Setting* setting;
};

