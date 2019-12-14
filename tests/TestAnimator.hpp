#pragma once

#ifdef _TEST_RUN__

#include <LApp/LAppDelegate.hpp>
#include "Communicator.hpp"
#include "detection.h"
#include <QApplication>

class TestAnimator {
public:
	static int runTest(int argc, char *argv[]) {

		FacialLandmarkDetector::getInstance()->startDetector();

		// create the application instance
		if (LAppDelegate::GetInstance()->Initialize() == GL_FALSE)
		{
			return 1;
		}

		LAppDelegate::GetInstance()->startThreadRun();


		return 0;
	}

private:

};

#endif