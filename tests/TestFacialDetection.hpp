#pragma once

#ifdef _TEST_RUN__

#include <nlohmann/json.hpp>
#include "detection.h"
#include "Network.h"
#include <iostream>

class TestFacialDetection {
public:
	static void runTest() {
		using std::cout;	using std::endl;

		auto dummyHandle = FacialLandmarkDetector::getInstance();	// Force the construction of the singleton instance
		while (true) {
			system("pause");
			auto j = Network::getInstance()->getSendJson();
			cout << *j << endl;
		}
	}

private:
	TestFacialDetection() = default;
	TestFacialDetection(const TestFacialDetection&) = delete;

private:
	const nlohmann::json* _json = nullptr;
};

#endif