#include "Communicator.hpp"
#include "detection.h"
#include "Network_QT.h"


using namespace Csm;

Communicator* Communicator::s_instance = nullptr;

Communicator::Communicator() {

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
	const nlohmann::json* temp = Network_QT::getInstance()->getSendJson();
	if (temp == nullptr 
		|| (*temp)["data"].is_null() ) {
		return nullptr;
	}
	else {
		return temp;
	}
}
