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
#include "shared_constants.h"

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

			bool skip_line = check_line(line);
cout << "skip line " << skip_line << endl;

			if (skip_line == false) {
//				cmdline_parser::decode_line(line, object, type, title, x_centre, y_centre, width, height, colour, direction);
				decode_line(line);
			}
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

bool cmdline_parser::check_line(std::string line) {
	bool no_data_in_line = false;
	std::string word("");
	if (shared_constants::comment.length() < line.length()) { 
		no_data_in_line = false;
		for (std::string::size_type char_no=0; char_no < shared_constants::comment.length(); char_no++) {
			word.push_back(line.at(char_no));
		}
	} else {
		no_data_in_line = true;
	}

	bool skip_line = false;

	LOG_INFO(logging::verb_level_e::DEBUG,"[Decode] Comment: ", shared_constants::comment, " Current line ", word);
	cout << "[Decode] Comment: " << shared_constants::comment << " Current line " << word << endl;

	if ((shared_constants::comment.compare(word) == 0) | (no_data_in_line == true)) {
		skip_line = true;
	} else {
		skip_line = false;
	}

	return skip_line;
}


//void cmdline_parser::decode_line(std::string line, cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction) {
void cmdline_parser::decode_line(std::string line) {

	// Not a comment
	// Start at the start of the line (position 1)
	std::string var_name("");
	std::string::size_type var_name_start = 1;
	std::string::size_type var_name_end = 0;
	bool var_name_valid = cmdline_parser::extract_word(line, var_name_start, var_name, var_name_end);
	ASSERT(var_name_valid == true);

	std::string var_value("");
	std::string::size_type var_value_start = var_name_end + 1;
	std::string::size_type var_value_end = 0;

	bool var_value_valid = cmdline_parser::extract_word(line, var_value_start, var_value, var_value_end);

	ASSERT(var_value_valid == true);
	ASSERT(var_value_end <= line.length());

	LOG_INFO(logging::verb_level_e::DEBUG,"[Decode] Variable Name: ", var_name, " Value: ", var_value);
	cout << "[Decode] Variable: " << var_name << " Value " << var_value << endl;

}

int cmdline_parser::extract_word(std::string line, std::string::size_type start_pos, std::string & word, std::string::size_type & end_pos) {
	std::string search_char(" ");

	ASSERT(start_pos > 0);
	ASSERT(start_pos < line.length());

	// Make a local copy of line and chop off the first start_ps characters
	std::string line_cpy = line;
	line_cpy.erase(0, (start_pos-1));

	std::string::size_type char_cnt = 0;

	// If line starting with search character, keep going
	while (search_char.compare(line_cpy.substr(char_cnt,1)) == 0) {
		char_cnt++;
	}

	// compare return 0 when the 2 strings are identical
	while((search_char.compare(line_cpy.substr(char_cnt,1)) != 0) && (char_cnt < line_cpy.length())) {
		word.push_back(line_cpy.at(char_cnt));
		char_cnt++;
	}

	LOG_INFO(logging::verb_level_e::DEBUG,"[Extract Word] Word found: ", word);

	// -1 because char_cnt point to the character where the space is
	end_pos = start_pos + (char_cnt - 1);

	LOG_INFO(logging::verb_level_e::DEBUG,"[Extract Word] Word found: ", word, " Last character position: ", end_pos);
	cout << "[Extract Word] Word: " << word << " End Pos " << end_pos << endl;
	cout << "[Extract Word] char_cnt: " << char_cnt << " line_cpy length " << line_cpy.length() << endl;


	bool valid = (word.compare("") != 0);
	return valid;

}

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