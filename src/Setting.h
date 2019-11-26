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
	}

	cv::Mat getProfile() {
		return profilePhoto;
	}
	std::string getName() {
		return name;
	}

	std::string getModelID() {
		return modelID;
	}

private:
	Setting() {};
	Setting(Setting&);
	static bool inited;
	short listenPort;
	short callPort;
	short maximumListenQueue;
	static Setting* setting;
	std::string name;
	std::string modelID;
	cv::Mat profilePhoto;
	std::vector<std::string> MACBlackList;
};

bool Setting::inited = false;
Setting* Setting::setting = nullptr;