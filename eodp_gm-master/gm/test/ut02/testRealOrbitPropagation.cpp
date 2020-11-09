// testRealOrbitPropagation.cpp
// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <stdlib.h>
#include <dirent.h>
#include <experimental/filesystem>
#include "GeometryModule.hpp"
#include <chrono>

TEST_CASE("Process the Geometry Module", "[exec_GM]")
{
	std::cout << "TEST_CASE [exec_GM]: Process the Geometry Module" << std::endl;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	try
	{
		char * res = realpath("./geometry_module", NULL);
		if (!res)
		{
			std::cout << "Error getting real path." << endl;
		}
		char arg1[] = "../conf/gm_local_conf.xml";
		char arg2[] = "../gm/test/ut02/output";
		char *argv[] = {&res[0], &arg1[0], &arg2[0], NULL};
		int argc = (int) (sizeof(argv) / sizeof(char*)) - 1;

		// Declare processor
		std::cout << "Declare processor" << std::endl;
		shared_ptr<GeometryModule> processor = make_shared<GeometryModule>();

		// Initialize module if it is not been initialized yet
		std::cout << "Initialize the geometry module." << endl;
		processor->initModule(GEOMETRY_MODULE_NAME, argc, argv);
		std::cout << "End initialize the geometry module." << endl;

		// Run the processor
		processor->processModule();

		free(res);

		std::cout << "TEST_CASE [exec_GM]: Finished succesfully!" << std::endl;

	}
	catch (GMException &e)
	{
		FAIL_CHECK("TEST_CASE [exec_GM]: Got an exception: " + string(e.what()));
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	// Processing time
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}


