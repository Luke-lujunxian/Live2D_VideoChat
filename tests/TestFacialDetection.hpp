#pragma once

#ifdef _TEST_RUN__

#include <nlohmann/json.hpp>
#include "detection.h"
#include "Network_QT.h"
#include <iostream>
#include <QTextStream>
#include <JsonConverter.hpp>
#include <LApp/LAppPal.hpp>

class TestFacialDetection {
public:
	static void runTest() {
		// Cubism Framework initialization
		LAppAllocator allocator;
		Csm::CubismFramework::StartUp(&allocator);
		Csm::CubismFramework::Initialize();

		auto _ = FacialLandmarkDetector::getInstance();	// Force the construction of the singleton instance
		FacialLandmarkDetector::getInstance()->startDetector();
		while (true) {
			system("pause");

			auto j = Network_QT::getInstance()->getSendJson();
			if ((*j)["data"].is_null()) {
				qDebug().noquote() << QString("null\n");
			}
			else {
				using namespace Csm;

				csmByte* buffer;	csmSizeInt size;
				Utils::CubismJson* cuJson = JsonConverter::convert(j, &buffer, &size);
				const char* text = cuJson->GetRoot().GetString().GetRawString();
				qDebug().noquote() << QString(text);
				LAppPal::ReleaseBytes(buffer);
				Utils::CubismJson::Delete(cuJson);
			}
		}


		// Cubism Framework disposal
		Csm::CubismFramework::Dispose();
	}

private:
	TestFacialDetection() = default;
	TestFacialDetection(const TestFacialDetection&) = delete;
};

#endif