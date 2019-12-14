#include "Communicator.hpp"
#include "detection.h"
#include "Network_QT.h"


using namespace Csm;

Communicator* s_instance = nullptr;

Communicator::Communicator() {
	QObject::connect(FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection,
					this, &Communicator::fetchFacialData);
}

void Communicator::releaseInstance() {
	delete s_instance;
}

Communicator* Communicator::getInstance() {
	if (s_instance == nullptr) {
		s_instance = new Communicator();
	}
	return s_instance;
}

const nlohmann::json* Communicator::getFacialData() {
	if (!_isUpdated) {
		return nullptr;
	}
	else {
		_isUpdated = false;
		return _facialData;
	}
}

void Communicator::fetchFacialData() {
	const nlohmann::json* temp = Network_QT::getInstance()->getSendJson();
	if (temp == nullptr
		|| (*temp)["data"].is_null()) {
		_isUpdated = false;
	}
	else {
		_facialData = temp;
		_isUpdated = true;
	}
}