
#include "LApp/LAppAllocator.hpp"

#define _TEST_RUN__
#include "../tests/TestFacialDetection.hpp"
#undef _TEST_RUN__


int main(int argc, char *argv[]) {
	using namespace Live2D::Cubism::Framework;

	// Cubism Framework initialization
	LAppAllocator allocator;
	CubismFramework::StartUp(&allocator);
	CubismFramework::Initialize();

	// Do something here
	TestFacialDetection::runTest();

	
	system("pause");

	// Cubism Framework disposal
	CubismFramework::Dispose();
}
