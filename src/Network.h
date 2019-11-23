#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
using namespace std;
using namespace nlohmann;

class Network {

public:
	void networkInit();
	void updateMotion(json motion);
	vector<json>* getMotion();
	static Network* getInstance();
	bool shouldStop() {
		return stopFlag;
	}

private:
	vector<json> displayObjects;
	json sendObject;
	Network();
	Network(Network&) = delete;
	Network& operator=(Network) = delete;
	thread listener;
	static Network* network;
	bool stopFlag;

	//Warning: All Network will end
	void stop() {
		stopFlag = true;
	}
	
};


