
#include "LApp/LAppAllocator.hpp"
#include "Communicator.hpp"

#define _TEST_RUN__
#include "../tests/TestAnimator.hpp"
#undef _TEST_RUN__


int main(int argc, char *argv[]) {
	using namespace Live2D::Cubism::Framework;

	// Cubism Framework initialization
	//LAppAllocator allocator;
	//CubismFramework::StartUp(&allocator);
	//CubismFramework::Initialize();


	// Other initializations
	Communicator::initialize();

	// Do something here
	TestAnimator::runTest();
	

	// Cubism Framework disposal
	//CubismFramework::Dispose();
}
