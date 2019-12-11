
#include "LApp/LAppAllocator.hpp"

#define _TEST_RUN__
#include "../tests/TestFacialDetection.hpp"
#undef _TEST_RUN__


int main() {
	using namespace Live2D::Cubism::Framework;

	// Cubism Framework initialization
	LAppAllocator allocator;
	CubismFramework::StartUp(&allocator);
	CubismFramework::Initialize();

	// Do something here
	TestFacialDetection::runTest();
	

	// Cubism Framework disposal
	CubismFramework::Dispose();

	system("pause");
}
