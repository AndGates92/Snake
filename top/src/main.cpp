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
#include <unistd.h>
#include <csignal>
#include "logging.h"
#include "trace_logging.h"
#include "graphics.h"
#include "file.h"
#include "main.h"
#include "custom_exception.h"

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
 * --> -i  \<filename\> : settings file
 * --> -hw \<0|1\>      : hard wall flag
 * --> -a  \<0|1\>      : auto-ride flag
 *
 */
int main (int argc, char ** argv) {

	signal(SIGSEGV, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGINT,  signal_handler);

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
		trace_logging::print_backtrace(STDERR_FILENO);
		std::cerr << "Snake game exception: " << cust_e.what();
	}

	LOG_INFO(logging::verb_level_e::ZERO, "End program Snake");

	return EXIT_SUCCESS;
}

/** 
 * @brief Function: void signal_handler()
 *
 * Signal handler. Prints backtrace
 */
void signal_handler(int sig_id) {
	LOG_INFO(logging::verb_level_e::ZERO, "Got signal ", sig_id);
	trace_logging::print_backtrace(STDERR_FILENO);
}
/** @} */ // End of addtogroup Main group
