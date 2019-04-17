/**
 * @copyright
 * @file settings.cpp
 * @author Andrea Gianarda
 * @date 17th April 2019
 * @brief Settings function
 */

#include <iostream>

#include "settings.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace settings;

// ================================================================
// Get functions
// ================================================================
bool settings::Settings::get_hard_wall_flag() {
	return this->hard_wall;
}

std::string settings::Settings::get_save_filename() {
	return this->save_filename;
}
// ================================================================
// Set functions
// ================================================================
void settings::Settings::set_hard_wall_flag(bool value) {
	this->hard_wall = value;
}

void settings::Settings::set_save_filename(std::string name) {
	this->save_filename = name;
}

void settings::Settings::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Hard Wall: ", this->hard_wall, " Save fiename: ", this->save_filename);
}

settings::Settings::~Settings() {
//	std::string pretext ("Settings Constructor");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}
