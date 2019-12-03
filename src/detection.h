#pragma once
#include <thread>
#include <vector>
#include <nlohmann/json.hpp>
#include <opencv.hpp>
#include <Network.h>
#include <Setting.h>


typedef struct RawFacePos {
	float angle;//+clockwise TODO
	bool inited = true;
	int faceLeftX;
	int faceRightX;
	int faceDownY, faceTopY;
	int noseMiddleMaxX, noseMiddleMinX, noseMiddleMaxY, noseMiddleMinY;
	int leftEyebrowY;
	int rightEyebrowY;
	int leftEyeMinX, leftEyeMaxX, leftEyeMinY, leftEyeMaxY;
	int rightEyeMinX, rightEyeMaxX, rightEyeMinY, rightEyeMaxY;
	int LipsInnerMaxY, LipsInnerMinY;
	cv::Vec3f leftIris;
	cv::Vec3f rightIris;
};

class FacialLandmarkDetector {
private:
	void detection();
	FacialLandmarkDetector() {
		debug = Setting::getSetting()->getDebugMode();
		nuturalFace.inited = false;
		captureNuturalFaceFlag = false;
		detectThread = nullptr;
		starDetector();
	};
	~FacialLandmarkDetector() {
		detectThread->join();
	}
	FacialLandmarkDetector(FacialLandmarkDetector&) = delete;
	FacialLandmarkDetector operator=(FacialLandmarkDetector) = delete;
	std::thread* detectThread;
	static FacialLandmarkDetector* facialLandmarkDetector;
	RawFacePos nuturalFace;
	bool captureNuturalFaceFlag;
public:
	bool CameraInitError;
	bool ModelLoadError;
	bool MultipleFaceWarning;
	bool debug;
	static FacialLandmarkDetector* getInstance() {
		if (facialLandmarkDetector == NULL) {
			facialLandmarkDetector = new FacialLandmarkDetector();
		}
		return facialLandmarkDetector;
	}
	void starDetector() {
		if (detectThread != nullptr && detectThread->joinable()) {
			throw "Already Running";
		}
		else {
			CameraInitError = false;
			ModelLoadError = false;
			MultipleFaceWarning = false;
			detectThread = new std::thread(&FacialLandmarkDetector::detection, this);
		}
	}
	//Blocking!
	//call and dones
	void captureNuturalFace() {
		captureNuturalFaceFlag = true;
		while (captureNuturalFaceFlag) {}
	}

};


