#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
using namespace nlohmann;


class Network {

public:
	void networkInit();
	void updateMotion(json motion);
	std::vector<json>* getMotion();
	bool shouldStop() {
		return stopFlag;
	}
	static Network* getInstance() {
		if (network == nullptr)
			network = new Network();
		return network;
	}

private:
	std::vector<json> displayObjects;
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

