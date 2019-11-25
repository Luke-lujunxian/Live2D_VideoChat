#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <guiddef.h>
#include <time.h>
using namespace nlohmann;

//https://lowrey.me/guid-generation-in-c-11/
#include <sstream>
#include <random>
#include <string>

unsigned int random_char() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return dis(gen);
}

std::string generate_hex(const unsigned int len) {
	std::stringstream ss;
	for (auto i = 0; i < len; i++) {
		const auto rc = random_char();
		std::stringstream hexstream;
		hexstream << std::hex << rc;
		auto hex = hexstream.str();
		ss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return ss.str();
}

std::string GenerateGuid()
{
	return generate_hex(8) + '-' + generate_hex(4) + '-' + generate_hex(4) + '-' + generate_hex(4) + '-' + generate_hex(12);
}

typedef enum LatencyState{NORMAL,DELAY,DISCONNECTED};

class MotionObject {
private:
	std::string sessionId;
	json motion;
	clock_t lastSuccessful;
public:
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

private:
	std::vector<MotionObject*> displayObjects;
	json sendObject;
	Network();
	Network(Network&) = delete;
	Network& operator=(Network) = delete;
	std::thread listener;
	bool stopFlag;
	static Network* network;

	//Warning: All Network will end
	void stop() {
		stopFlag = true;
	}
	
};

Network* Network::network = nullptr;

