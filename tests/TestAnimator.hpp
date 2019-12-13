#pragma once

#ifdef _TEST_RUN__

#include <LApp/LAppDelegate.hpp>
#include "detection.h"

class TestAnimator {
public:
	static int runTest() {
		auto dummyHandle = FacialLandmarkDetector::getInstance();

		qDebug().noquote() << "[CheckPoint1]";
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