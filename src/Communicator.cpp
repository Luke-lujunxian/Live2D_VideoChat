#include "Communicator.hpp"
#include "detection.h"
#include "Network_QT.h"
#include <chrono>
#include <thread>

using namespace Csm;

Communicator* Communicator::s_instance = nullptr;

Communicator::Communicator() {
	QObject::connect(
		FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection,
		this, &Communicator::fetchJson);
}

void Communicator::initialize() {
	s_instance = new Communicator();
}

void Communicator::dispose() {
	delete s_instance;
}

const Communicator* Communicator::getInstance() {
	if (s_instance == nullptr) {
		initialize();
	}
	return s_instance;
}

const nlohmann::json* Communicator::getNJson() const {
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

	const nlohmann::json* temp = Network_QT::getInstance()->getSendJson();
	if (temp != nullptr && temp != _last_received_json) {
		_last_received_json = _current_received_json;
		_current_received_json = temp;
	}
}
