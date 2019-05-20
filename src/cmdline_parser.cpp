/**
 * @copyright
 * @file cmdline_parser.cpp
 * @author Andrea Gianarda
 * @date 20th May 2019
 * @brief Command line parser
 */

#include <iostream>
#include <fstream>
#include <cstring>

#include "settings.h"
#include "logging.h"
#include "snake_list.h"
#include "obstacle.h"
#include "cmdline_parser.h"

using namespace std;
using namespace logging;
using namespace snake_list;
using namespace obstacle;

namespace cmdline_parser {
	/** @defgroup CmdlineParserGroup Command Line Parser Doxygen Group
	 *  Command Lie Parser functions and classes
	 *  @{
	 */

	namespace {
		/**
		 * @brief input file option
		 *
		 */
		const char* input_file_opt = "-i";

		/**
		 * @brief input file name
		 *
		 */
		string input_filename("");

	}
}

void cmdline_parser::parse(int argc, char** argv) {
	LOG_INFO(logging::verb_level_e::ZERO,"[Parse] Command line:");
	LOG_INFO(logging::verb_level_e::ZERO,"[Parse] Number of arguments ",  argc);
	for (int arg_no = 0; arg_no < argc; arg_no++) {
		LOG_INFO(logging::verb_level_e::ZERO,"[Parse] \targument ", arg_no, ": ", argv[arg_no]);
	}

	int input_file_pos = -1;

	for (int arg_no = 1; arg_no < argc; arg_no++) {
		if (!(strcmp(argv[arg_no],input_file_opt))) {
			if (input_file_pos > 0) {
				LOG_ERROR("Input file has already been provided as an argument. Previous argument position was ", input_file_pos, ". New argument position is ", (arg_no+1))
			}
			if (argc < (arg_no+1)) {
				LOG_ERROR("Input filename not given as number of arguments is ", argc, " and filename expected position number is ", (arg_no+1))
			}
			input_file_pos = arg_no+1;
			LOG_INFO(logging::verb_level_e::DEBUG,"[Parse] Training Set argument number: ",  (input_file_pos/2));
		}
	}

	if (input_file_pos > 0) {
		input_filename.assign(argv[input_file_pos]);
		LOG_INFO(logging::verb_level_e::LOW,"[Parse] \tInput filename: ", input_filename);
	}
}
