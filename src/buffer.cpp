
// [Credit]
// The implementation of the functions in this file is mostly copied 
// from the demo given by Live2D SDK.

#include "buffer.hpp"
#include <sys/stat.h>
#include <exception>
#include <ifstream>

using namespace Csm;

Csm::csmByte* loadFileAsBytes(const std::string& filePath, Csm::csmSizeInt* outSize) {
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

void releaseBytes(Csm::csmByte* byteData) {
	delete[] byteData;
}
