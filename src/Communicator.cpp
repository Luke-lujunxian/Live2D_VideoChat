#include "Communicator.hpp"
#include "detection.h"
#include "Network_QT.h"
#include <chrono>
#include <thread>

using namespace Csm;

void Communicator::initialize() {
	s_self = new Communicator();
	QObject::connect(FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection,
					s_self, &Communicator::fetchJson);
}

void Communicator::dispose() {
	delete s_self;
}

const nlohmann::json* Communicator::getValidNJson() const {
	if (_current_received_json == nullptr
		|| (*_current_received_json)["data"].is_null()) {
		return nullptr;
	}
	else {
		return _current_received_json;
	}
}


void Communicator::fetchJson() {
	std::this_thread::sleep_for(std::chrono::microseconds(100));	// Wait for the writing process to complete

	nlohmann::json* temp = Network_QT::getInstance()->getSendJson();
	if (temp != nullptr && temp != _last_received_json) {
		_last_received_json = _current_received_json;
		_current_received_json = temp;
	}
}