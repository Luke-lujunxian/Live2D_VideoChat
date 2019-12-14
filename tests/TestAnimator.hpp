#pragma once

#ifdef _TEST_RUN__

#include <LApp/LAppDelegate.hpp>
#include "Communicator.hpp"
#include "detection.h"

class TestAnimator {
public:
	static int runTest() {
		// Initializations
		auto _ = FacialLandmarkDetector::getInstance();	// Force the construction of the singleton instance
		FacialLandmarkDetector::getInstance()->startDetector();
		Communicator::initialize();

		// create the application instance
		if (LAppDelegate::GetInstance()->Initialize() == GL_FALSE)
		{
			return 1;
		}

		LAppDelegate::GetInstance()->Run();

		return 0;
	}

private:

};

#endif