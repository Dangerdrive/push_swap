#include <gtest/gtest.h>

// Include other necessary files
// #include "TestHelpers.cpp" // Only if you have implementations that need to be included

int main(int argc, char **argv) {
	// Initialize Google Test
	::testing::InitGoogleTest(&argc, argv);

	// Perform global setup if needed

	// Run all tests
	int retVal = RUN_ALL_TESTS();

	// Perform global teardown if needed

	return retVal;
}