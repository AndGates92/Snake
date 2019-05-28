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
#include <cmath>

#include "graphics.h"
#include "game_graphics.h"
#include "settings.h"
#include "utility.h"
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

		/**
		 * @brief default value for strings
		 *
		 */
		string string_default("");

		/**
		 * @brief default value for integers
		 *
		 */
		int int_default = -1;

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
	game_graphics::set_snake_settings();
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
			bool skip_line = check_line(line);

			if (skip_line == false) {
				std::string var_name("");
				std::string var_value("");
				cmdline_parser::decode_line(line, var_name, var_value);
				cmdline_parser::assign_common_var(var_name, var_value, object, type, title, x_centre, y_centre, width, height, colour, direction);
			}
			line_count++;
		}

		if (object != cmdline_parser::obj_e::UNKNOWN) {
			cmdline_parser::create_obj(object, type, title, x_centre, y_centre, width, height, colour, direction);
		}
	}

}

void cmdline_parser::reset_common_var(cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction) {
	object = cmdline_parser::obj_e::UNKNOWN;
	type = string_default;
	title = string_default;
	x_centre = int_default;
	y_centre = int_default;
	width = int_default;
	height= int_default;
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

	if ((shared_constants::comment.compare(word) == 0) | (no_data_in_line == true)) {
		skip_line = true;
	} else {
		skip_line = false;
	}

	return skip_line;
}

void cmdline_parser::decode_line(std::string line, std::string & var_name, std::string & var_value) {

	// Not a comment
	// Start at the start of the line (position 1)
	std::string::size_type var_name_start = 1;
	std::string::size_type var_name_end = 0;
	bool var_name_valid = cmdline_parser::extract_word(line, var_name_start, var_name, var_name_end);
	ASSERT(var_name_valid == true);

	cmdline_parser::delete_special_characters(var_name);

	std::string::size_type var_value_start = var_name_end + 1;
	std::string::size_type var_value_end = 0;

	bool var_value_valid = cmdline_parser::extract_word(line, var_value_start, var_value, var_value_end);

	ASSERT(var_value_valid == true);
	ASSERT(var_value_end <= line.length());

	LOG_INFO(logging::verb_level_e::DEBUG,"[Decode] Variable Name: ", var_name, " Value: ", var_value);

}

void cmdline_parser::assign_common_var(std::string var_name, std::string var_value, cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction) {

	if ((var_name.compare("TYPE") == 0) | (var_name.compare("Type") == 0) | (var_name.compare("type") == 0)) {
		if (object != cmdline_parser::obj_e::UNKNOWN) {
			cmdline_parser::create_obj(object, type, title, x_centre, y_centre, width, height, colour, direction);
		}
		cmdline_parser::reset_common_var(object, type, title, x_centre, y_centre, width, height, colour, direction);
		type = var_value;
		object = cmdline_parser::str_to_obj(var_value);
	} else if ((var_name.compare("TITLE") == 0) | (var_name.compare("Title") == 0) | (var_name.compare("title") == 0)) {
		title = var_value;
	} else if ((var_name.compare("X") == 0) | (var_name.compare("x") == 0)) {
		x_centre = utility::str_to_int(var_value);
	} else if ((var_name.compare("Y") == 0) | (var_name.compare("y") == 0)) {
		y_centre = utility::str_to_int(var_value);
	} else if ((var_name.compare("WIDTH") == 0) | (var_name.compare("Width") == 0) | (var_name.compare("width") == 0)) {
		width = utility::str_to_int(var_value);
	} else if ((var_name.compare("HEIGHT") == 0) | (var_name.compare("Height") == 0) | (var_name.compare("height") == 0)) {
		height = utility::str_to_int(var_value);
	} else if ((var_name.compare("COLOUR") == 0) | (var_name.compare("Colour") == 0) | (var_name.compare("colour") == 0)) {
		colour = colours::str_to_colour(var_value);
	} else if ((var_name.compare("DIRECTION") == 0) | (var_name.compare("Direction") == 0) | (var_name.compare("direction") == 0)) {
		direction = snake_utils::str_to_direction(var_value);
	} else if ((var_name.compare("DUMP") == 0) | (var_name.compare("Dump") == 0) | (var_name.compare("dump") == 0)) {
		snake_settings.set_dump_filename(var_value);
	} else if ((var_name.compare("SAVE") == 0) | (var_name.compare("Save") == 0) | (var_name.compare("save") == 0)) {
		snake_settings.set_save_filename(var_value);
	} else if ((var_name.compare("SPEED") == 0) | (var_name.compare("Speed") == 0) | (var_name.compare("speed") == 0)) {
		snake_settings.set_speed(utility::str_to_int(var_value));
	} else if ((var_name.compare("SNAKEUNITS") == 0) | (var_name.compare("SnakeUnits") == 0) | (var_name.compare("Snakeunits") == 0) | (var_name.compare("snakeunits") == 0)) {
		snake_settings.set_snake_units(utility::str_to_int(var_value));
	} else if ((var_name.compare("OBSTACLES") == 0) | (var_name.compare("Obstacles") == 0) | (var_name.compare("obstacles") == 0)) {
		snake_settings.set_obs_no(utility::str_to_int(var_value));
	} else if ((var_name.compare("SCORE") == 0) | (var_name.compare("Score") == 0) | (var_name.compare("score") == 0)) {
		snake_settings.set_score(utility::str_to_int(var_value));
	} else {
		LOG_ERROR("Unknown variable name: ", var_name);
	}

}

void cmdline_parser::delete_special_characters(std::string & word) {
	for (std::string::size_type char_no=0; char_no < word.length(); char_no++) {
		if ( ((word.at(char_no) >= 'a') & (word.at(char_no) <= 'z')) |
		     ((word.at(char_no) >= 'A') & (word.at(char_no) <= 'Z')) |
		     ((word.at(char_no) >= '0') & (word.at(char_no) <= '9')) ) {
			// No action if alpha-numerical character
			continue;
		} else {
			word.erase(char_no,1);
		}
	}
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
		case cmdline_parser::obj_e::SETTINGS:
			os << "SETTINGS";
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

// Convert string to object type obj_e
cmdline_parser::obj_e cmdline_parser::str_to_obj (std::string type) {

	cmdline_parser::obj_e obj = cmdline_parser::obj_e::UNKNOWN;

	if ((type.compare("SNAKE") == 0) | (type.compare("Snake") == 0) | (type.compare("snake") == 0)) {
		obj = cmdline_parser::obj_e::SNAKE;
	} else if ((type.compare("OBSTACLE") == 0) | (type.compare("Obstacle") == 0) | (type.compare("obstacle") == 0)) {
		obj = cmdline_parser::obj_e::OBSTACLE;
	} else if ((type.compare("WINDOW") == 0) | (type.compare("Window") == 0) | (type.compare("window") == 0)) {
		obj = cmdline_parser::obj_e::WINDOW;
	} else if ((type.compare("MENU") == 0) | (type.compare("Menu") == 0) | (type.compare("menu") == 0)) {
		obj = cmdline_parser::obj_e::MENU;
	} else if ((type.compare("SETTINGS") == 0) | (type.compare("Settings") == 0) | (type.compare("settings") == 0)) {
		obj = cmdline_parser::obj_e::SETTINGS;
	} else if ((type.compare("TILE") == 0) | (type.compare("Tile") == 0) | (type.compare("tile") == 0)) {
		obj = cmdline_parser::obj_e::TILE;
	} else if ((type.compare("UNKNOWN") == 0) | (type.compare("Unknown") == 0) | (type.compare("unknown") == 0)) {
		obj = cmdline_parser::obj_e::UNKNOWN;
	} else {
		obj = cmdline_parser::obj_e::UNKNOWN;
		LOG_ERROR("Unknown object type: ", type);
	}

	return obj;
}

// Create object
void cmdline_parser::create_obj(cmdline_parser::obj_e object, std::string type, std::string title, int x_centre, int y_centre, int width, int height, colours::palette_e colour, snake_utils::direction_e direction) {

	LOG_INFO(logging::verb_level_e::DEBUG, "[Create Object] Variables:\n\t	object-> ", object, "\n\tType-> ", type, "\n\tTitle-> ", title, "\n\tCoordinates-> (", x_centre, ", ", y_centre, ")\n\t Dimensions: Width-> ", width, " Height-> ", height, "\n\tDirection-> ", direction, "\n\tColour-> ", colour);

	int id = 0;

	switch (object) {
		case cmdline_parser::obj_e::SNAKE:
			game_graphics::add_snake_node(x_centre, y_centre, width, height, direction, colour);
			break;
		case cmdline_parser::obj_e::OBSTACLE:
			game_graphics::add_obs_node(x_centre, y_centre, width, height, colour);
			break;
		case cmdline_parser::obj_e::WINDOW:
			id = graphics_utils::win_node_add(title, type, width, height, x_centre, y_centre, colour);
			graphics::set_id(id, title);
			break;
		case cmdline_parser::obj_e::TILE:
			snake_settings.set_tile_width(width);
			snake_settings.set_tile_height(height);
			break;
		case cmdline_parser::obj_e::MENU:
		case cmdline_parser::obj_e::SETTINGS:
		case cmdline_parser::obj_e::UNKNOWN:
			LOG_INFO(logging::verb_level_e::ZERO, "[Create Object] Calling create_obj for object: ", object, ". No action to be take");
			break;
		default:
			LOG_ERROR("[Create Object] Unknown object: ", object);
			break;
	}
}
