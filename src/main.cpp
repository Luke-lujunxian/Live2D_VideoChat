
#include "LApp/LAppAllocator.hpp"
#include "Communicator.hpp"

#define _TEST_RUN__
#include "../tests/TestMainWindow.hpp"
#include "../tests/TestAnimator.hpp"
#undef _TEST_RUN__


int main(int argc, char *argv[]) {

	// Do something here
	return TestAnimator::runTest();

}
