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
#include "file.h"
#include "snake_list.h"
#include "obstacle.h"
#include "cmdline_parser.h"

using namespace std;
using namespace logging;
using namespace iofile;
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

void cmdline_parser::process() {
	cmdline_parser::extract_inputfile_info();
}

void cmdline_parser::extract_inputfile_info() {
	// If input_filename is equal to an empty string means that it has not been changed
	if (input_filename.compare("") == 0) {
		LOG_ERROR("Input file has not been detected");
	} else {
		iofile::File input_file(input_filename, iofile::mode_e::RO);
		input_file.open_ifile();
		std::ifstream & ifile = input_file.get_ifile();
		int line_count = 0;
		cmdline_parser::obj_e object;
		std::string type;
		std::string title;
		int x_centre;
		int y_centre;
		int width;
		int height;
		colours::palette_e colour;
		snake_utils::direction_e direction;

		cmdline_parser::reset_common_var(object, type, title, x_centre, y_centre, width, height, colour, direction);

		for (std::string line; std::getline(ifile, line); ) {
			LOG_INFO(logging::verb_level_e::DEBUG,"[Process] Line cont ,", line_count, ": ", line);
cout << "Line no " << line_count << ": " << line << endl;
//			decode_line(line, object, type, title, x_centre, y_centre, width, height, colour, direction);
			line_count++;
		}
	}

}

void cmdline_parser::reset_common_var(cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction) {
	object = cmdline_parser::obj_e::UNKNOWN;
	type = "";
	title = "";
	x_centre = -1;
	y_centre = -1;
	width = -1;
	height= -1;
	colour = colours::palette_e::UNKNOWN;
	direction = snake_utils::direction_e::UNKNOWN;
	LOG_INFO(logging::verb_level_e::DEBUG, "Reset values of common variable:\n\t	object-> ", object, "\n\tType-> ", type, "\n\tTitle-> ", title, "\n\tCoordinates-> (", x_centre, ", ", y_centre, ")\n\t Dimensions: Width-> ", width, " Height-> ", height, "\n\tDirection-> ", direction);
}

//void cmdline_parser::decode_line(std::string line, cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction) {

//}

// Overload << operator for obj_e
std::ostream& cmdline_parser::operator<< (std::ostream& os, cmdline_parser::obj_e obj) {

	switch (obj) {
		case cmdline_parser::obj_e::SNAKE:
			os << "SNAKE";
			break;
		case cmdline_parser::obj_e::OBSTACLE:
			os << "OBSTACLE";
			break;
		case cmdline_parser::obj_e::WINDOW:
			os << "WINDOW";
			break;
		case cmdline_parser::obj_e::MENU:
			os << "MENU";
			break;
		case cmdline_parser::obj_e::SETTING:
			os << "SETTING";
			break;
		case cmdline_parser::obj_e::TILE:
			os << "TILE";
			break;
		case cmdline_parser::obj_e::UNKNOWN:
			os << "UNKNOWN";
			break;
		default:
			os << "Unknown object";
			break;
	}

	return os;
}
