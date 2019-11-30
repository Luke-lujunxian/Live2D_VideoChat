#pragma once
#include <thread>
#include <vector>
#include <nlohmann/json.hpp>


class FacialLandmarkDetector {
private:
	void detection();
	FacialLandmarkDetector() {
		debug = true;
		nuturalFace.inited = false;
		captureNuturalFaceFlag = false;
		starDetector();
	};
	~FacialLandmarkDetector() {
		detectThread->join();
	}
	FacialLandmarkDetector(FacialLandmarkDetector&) = delete;
	FacialLandmarkDetector operator=(FacialLandmarkDetector) = delete;
	static std::thread* detectThread;
	static FacialLandmarkDetector* facialLandmarkDetector;
	RawFacePos nuturalFace;
	bool captureNuturalFaceFlag;
public:
	bool CameraInitError;
	bool ModelLoadError;
	bool MultipleFaceWarning;
	bool debug;
	FacialLandmarkDetector* getInstance() {
		if (facialLandmarkDetector == nullptr) {
			facialLandmarkDetector = new FacialLandmarkDetector();
		}
		return facialLandmarkDetector;
	}
	void starDetector() {
		if (!detectThread->joinable()) {
			CameraInitError = false;
			ModelLoadError = false;
			MultipleFaceWarning = false;
			detectThread = new std::thread(&FacialLandmarkDetector::detection, this);
		}
		else {
			throw "Already Running";
		}
	}
	//Blocking!
	//call and dones
	void captureNuturalFace() {
		captureNuturalFaceFlag = true;
		while (captureNuturalFaceFlag) {}
	}

};
FacialLandmarkDetector* FacialLandmarkDetector::facialLandmarkDetector = nullptr;

typedef struct RawFacePos {
	float angle;//+clockwise TODO
	bool inited = true;
	int faceLeftX;
	int faceRightX;
	int faceDownY;
	int noseMiddleMaxX,noseMiddleMinX, noseMiddleMaxY, noseMiddleMinY;
	int leftEyebrowY;
	int rightEyebrowY;
	int leftEyeMinX, leftEyeMaxX, leftEyeMinY, leftEyeMaxY;
	int rightEyeMinX, rightEyeMaxX, rightEyeMinY, rightEyeMaxY;
	int LipsInnerMaxY, LipsInnerMinY;

};

