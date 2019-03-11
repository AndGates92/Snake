/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 04th February 2019
 * @brief Main function of the program
 */

#include <iostream>
#include "logging.h"
#include "graphics.h"
#include "file.h"

using namespace std;
using namespace logging;
using namespace graphics;

int main (int argc, char ** argv) {

	LOG_INFO(logging::verb_level_e::ZERO, "Start program Snake");

	init_graphics(argc, argv);

	LOG_INFO(logging::verb_level_e::ZERO, "End program Snake");

	return EXIT_SUCCESS;
}
