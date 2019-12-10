
#include "LApp/LAppAllocator.hpp"

#include "../tests/TestJsonConvert.hpp"


int main() {
	using namespace Live2D::Cubism::Framework;

	LAppAllocator allocator;
	CubismFramework::StartUp(&allocator);
	CubismFramework::Initialize();


	TestJsonConvert::runTest();


	CubismFramework::Dispose();

	system("pause");
}
