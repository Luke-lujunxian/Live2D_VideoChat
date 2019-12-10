
#include "LApp/LAppAllocator.hpp"

#define _TEST_RUN__
#include "../tests/TestJsonConvert.hpp"
#undef _TEST_RUN__


int main() {
	using namespace Live2D::Cubism::Framework;

	LAppAllocator allocator;
	CubismFramework::StartUp(&allocator);
	CubismFramework::Initialize();


	TestJsonConvert::runTest2();


	CubismFramework::Dispose();

	system("pause");
}
