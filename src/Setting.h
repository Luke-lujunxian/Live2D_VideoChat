#pragma once
/*
A single instance class to store and access global settings.



*/
#include <opencv.hpp>
#include <string>
class Setting {

public:
	static Setting* getSetting() {
		if (!Setting::inited)
			setting = new Setting();
		return setting;
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

	void setProfile(std::string addr) {
		//Probably some translate? / \?
		profilePhoto = cv::imread(addr);
		profiletype = addr.substr(addr.find_last_of('.')+1, addr.length() - addr.find_last_of('.') - 1);
	}

	cv::Mat getProfile() {
		return profilePhoto;
	}
	std::string getProfileType() {
		return profiletype;
	}
	std::string getName() {
		return name;
	}

	std::string getModelID() {
		return modelID;
	}

	bool getDebugMode() {
		return debug;
	}

private:
	Setting() {
		inited = true;
		listenPort = 1919;
		callPort = 1145;
		maximumListenQueue = 5;
		name = "Leader1";
		modelID = "Tasho koji";
		debug = false;
	};
	Setting(Setting&);
	static bool inited;
	short listenPort;
	short callPort;
	short maximumListenQueue;
	static Setting* setting;
	std::string name;
	std::string modelID;
	cv::Mat profilePhoto;
	std::string profiletype;
	std::vector<std::string> MACBlackList;
	bool debug;
};

