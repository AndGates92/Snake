/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 04th February 2019
 * @brief Main function of the program
 */

#include <iostream>
#include "log.h"
#include "graphics.h"

using namespace std;
using namespace log;
using namespace graphics;

int main (int argc, char ** argv) {

	LOG_INFO(log::verb_level_e::ZERO, "Start program Snake");

	init_graphics(argc, argv);
	test_graphics();

	LOG_INFO(log::verb_level_e::ZERO, "End program Snake");

	return EXIT_SUCCESS;
}
