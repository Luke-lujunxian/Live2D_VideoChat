
// [Credit]
// The implementation of the functions in this file is mostly copied 
// from the demo given by Live2D SDK.

#include "model_utils.hpp"
#include <sys/stat.h>
#include <exception>
#include <ifstream>

using namespace Csm;

static csmFloat32 s_deltaTime = 0.0f;
static csmFloat32 s_currentFrame = 0.0f;
static csmFloat32 s_lastFrame = 0.0f;

csmFloat32 getDeltaTime() {
	return s_deltaTime;
}

void updateTime() {
	throw std::exception("This function is not implemented yet");
	s_currentFrame = 42.0f;	// TODO: Call the timer function provided by Qt
	s_deltaTime = s_currentFrame - s_lastFrame;
	s_lastFrame = s_currentFrame;
}

csmByte* loadFileAsBytes(const std::string& filePath, csmSizeInt* outSize) {
	// Use stat() to obtain the size of the file
	int fileSize = 0;
	struct stat fileStatus;
	if (stat(filePath.c_str(), &fileStatus) == 0) {
		fielSize = fileStatus.st_size;
	}
	else {
		throw std::exception("System function stat() fails.");
	}

	char* buf = new char[fileSize];

	std::ifstream file(filePath, std::ifstream::binary);
	if (!file.is_open()) {
		throw std::exception(std::string("Cannot open file: ") + filePath);
	}

	file.read(buf, fileSize);
	file.close();

	*outSize = fileSize;
	return reinterpret_cast<csmByte*>(buf);
}

void releaseBytes(csmByte* byteData) {
	delete[] byteData;
}
