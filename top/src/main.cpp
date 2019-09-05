/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 04th February 2019
 * @brief Main function of the program
 */

#include <iostream>
#include <ctime>
#include <exception>
#include "logging.h"
#include "graphics.h"
#include "file.h"
#include "custom_exception.h"

using namespace std;
using namespace logging;
using namespace graphics;

/** @addtogroup MainGroup
 *  @{
 */
/** 
 * @brief Function: int main (int argc, char * argv[])
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 * \return an integer corresponging to the exit status
 *
 * Decodes the arguments and call functions for further processing
 *
 * Syntax:
 * --> -trs \<filename\> : training set file
 * --> -tes \<filename\> : test set file
 * --> -trl \<filename\> : training label file
 * --> -tel \<filename\> : test label file
 *
 */
int main (int argc, char ** argv) {

	try {
		LOG_INFO(logging::verb_level_e::ZERO, "Start program Snake");

		LOG_INFO(logging::verb_level_e::ZERO,"[Main] Verbosity level: ", VERBOSITY);
		LOG_INFO(logging::verb_level_e::DEBUG,"[Main] Command line:");
		LOG_INFO(logging::verb_level_e::DEBUG,"[Main] Number of arguments ",  argc);
		for (int i = 0; i < argc; i++) {
			LOG_INFO(logging::verb_level_e::DEBUG,"[Main] \targument ", i, ": ", argv[i]);
		}

		srand(time(NULL));

		graphics::init_graphics(argc, argv);
	} catch (custom_exception::CustomException cust_e) {
		std::cerr << "Snake game exception: " << cust_e.what();
	}

	LOG_INFO(logging::verb_level_e::ZERO, "End program Snake");

	return EXIT_SUCCESS;
}
/** @} */ // End of addtogroup Main group
