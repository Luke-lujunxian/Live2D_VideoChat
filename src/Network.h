#pragma once
#ifndef NETWORK_H
#define NETWORK_H


#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <guiddef.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <Base64.h>
using namespace nlohmann;

//https://lowrey.me/guid-generation-in-c-11/
#include <sstream>
#include <random>
#include <string>


unsigned int random_char();

std::string generate_hex(const unsigned int len);

std::string GenerateGuid();

typedef enum LatencyState{NORMAL,DELAY,DISCONNECTED};

class MotionObject {
private:
	std::string sessionId;
	json motion;
	clock_t lastSuccessful;
	cv::Mat profile;
	const std::string modelID;
public:
	std::string name;
	bool alive;
	MotionObject() {
		this->alive = true;
		this->sessionId = GenerateGuid();
		lastSuccessful = clock();
	}
	MotionObject(std::string sessionId) {
		this->alive = true;
		this->sessionId = sessionId;
	}

	void writeObject(std::string received) {
		json jtemp;
		try {
			jtemp = json::parse(received);

		}
		catch (json::exception e) {
			if (e.id == 101) {
				if (received == "") {
					//not Receiving
				}
				else {
					//data incorrect
				}
			}
			else {
				//unknown error
			}

			return;
		}

		motion = received;
		lastSuccessful = clock();
	}

	json* getMotion() {
		return &motion;
	}

	LatencyState getLatencyState() {
		int delay = clock(); - lastSuccessful;
		if(delay <= 300) {
			return NORMAL;
		}
		else if (delay > 300 && delay < 3000) {
			return DELAY;
		}
		else {
			return DISCONNECTED;
		}
	}

	void setProfileByBase64(std::string base64) {
		try {
			profile = Base2Mat(base64);
		}
		catch (int e) {
			//prifile = dafault
			return;
		}
	}
	
};



class Network {

public:
	void networkInit();
	void updateMotion(json& motion);
	std::vector<MotionObject*>* getDisplayObjects();
	json* getSendJson();
	bool shouldStop() {
		return stopFlag;
	}
	static Network* getInstance() {
		if (network == nullptr)
			network = new Network();
		return network;
	}
	void call(std::string, int);
	void call(std::string target);

private:
	std::vector<MotionObject*> displayObjects;
	json sendObject;
	Network();
	Network(Network&) = delete;
	Network& operator=(Network) = delete;
	std::thread* listener;
	bool stopFlag;
	static Network* network;

	//Warning: All Network will end
	void stop() {
		stopFlag = true;
	}
	
};



#endif // !NETWORK_H

