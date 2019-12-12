#pragma once
/*
A single instance class to store and access global settings.



*/
#include <opencv2/opencv.hpp>
#include <string>
#include <QtMultimedia/QAudioDeviceInfo>
class Setting {

public:
	static Setting* getSetting() {
		if (!Setting::inited)
			setting = new Setting();
		return setting;
	}
	short const getCameraID() {
		return cameraID;
	}
	bool setCameraID(short ID) {
		this->cameraID = ID;
		return true;
	}

	short const getListenPort() {
		return this->listenPort;
	}
	bool setListenPort(short port) {
		this->listenPort = port;
		return true;

	}

	short const getAudioPort() {
		return this->audioPort;
	}
	bool setAudioPort(short port) {
		this->audioPort = port;
		return true;

	}
	short const getCallPort() {
		return this->callPort;
	}
	bool setCallPort(short port) {
		this->callPort = port;
		return true;

	}

	short const getMaximumListenQueue() {
		return this->maximumListenQueue;
	}
	void setMaximumListenQueue(short maximumListenQueue) {
		 this->maximumListenQueue = maximumListenQueue;
	}

	bool setProfile(std::string addr) {
		//Probably some translate? / \?
		pathToProfile = addr;
		profilePhoto = cv::imread(addr);
		if (profilePhoto.data == NULL)
			return false;
		profiletype = addr.substr(addr.find_last_of('.') + 1, addr.length() - addr.find_last_of('.') - 1);
		return true;
	}
	std::string getProfilePath() {
		return pathToProfile;
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
	bool setName(std::string name) {
		if (name.length() < 4 || name.length() > 16)
			return false;
		this->name = name;
		return true;
	}

	std::string getModelID() {
		return modelID;
	}
	bool setModelID(std::string ModelID) {
		this->modelID = ModelID;
		return true;

	}
	void setInputDevice(QAudioDeviceInfo& device) {
		inputDevice = device;
	}
	void setOutputDevice(QAudioDeviceInfo& device) {
		outputDevice = device;
	}
	QAudioDeviceInfo getOutputDevice() {
		return outputDevice;
	}
	QAudioDeviceInfo getInputDevice() {
		return inputDevice;
	}
/*
	bool getDebugMode() {
		return debug;
	}
	void setDebugMode(bool mode) {
		debug = mode;
	}
*/
private:
	Setting() {
		inited = true;
		listenPort = 1919;
		callPort = 1145;
		maximumListenQueue = 5;
		audioPort = 893;
		name = "Leader1";
		modelID = "Tasho koji";
		debug = false;
		outputDevice = QAudioDeviceInfo::defaultOutputDevice();
		inputDevice = QAudioDeviceInfo::defaultInputDevice();
		pathToProfile = "..\\..\\res\\defaultProfile.jpg";
		showCamera = false;
		ShowFR = false;
	};
	Setting(Setting&);
	static bool inited;
	short cameraID;
	short listenPort;
	short callPort;
	short audioPort;
	short maximumListenQueue;
	static Setting* setting;
	std::string name;
	std::string modelID;
	cv::Mat profilePhoto;
	std::string profiletype;
	std::vector<std::string> MACBlackList;
	QAudioDeviceInfo outputDevice;
	QAudioDeviceInfo inputDevice;
	std::string pathToProfile;
public:
	bool debug;
	bool showCamera;
	bool ShowFR; // Show facial recognization image
};

