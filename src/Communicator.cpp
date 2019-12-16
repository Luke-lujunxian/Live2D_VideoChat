#include "Communicator.hpp"
#include "detection.h"
#include "Network_QT.h"


using namespace Csm;

Communicator* s_instance = nullptr;

Communicator::Communicator() {
	QObject::connect(FacialLandmarkDetector::getInstance(), &FacialLandmarkDetector::NewDetection,
					this, &Communicator::fetchSelfFacialData);
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

const nlohmann::json* Communicator::getSelfFacialData() {
	if (!_isSelfUpdated) {
		return nullptr;
	}
	else {
		_isSelfUpdated = false;
		return _selfFacialData;
	}
}

void Communicator::fetchSelfFacialData() {
	const nlohmann::json* temp = Network_QT::getInstance()->getSendJson();
	if (temp == nullptr
		|| (*temp)["data"].is_null()) {
		_isSelfUpdated = false;
	}
	else {
		_selfFacialData = temp;
		_isSelfUpdated = true;
	}
}