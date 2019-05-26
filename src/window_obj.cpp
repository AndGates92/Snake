/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief File function
 */

#include <iostream>

#include "window_obj.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace window_obj;


void window_obj::WindowObj::destroy_obj() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Destroy Window Object");
	this->drawing.destroy_window();
	this->action_list.destroy_menu();
}

window_obj::WindowObj::~WindowObj() {
	std::string pretext ("Window Object Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
	this->drawing.~Window();
	this->action_list.~Menu();
}

void window_obj::WindowObj::print_info(logging::verb_level_e verbosity, std::string pretext) {
	// Window content
	this->drawing.print_info(verbosity, pretext);
	// Menu
	this->action_list.print_info(verbosity, pretext);
}

int window_obj::WindowObj::get_win_id() {
	return this->drawing.get_id();
}

std::string window_obj::WindowObj::get_win_title() {
	return this->drawing.get_title();
}

int window_obj::WindowObj::get_menu_id() {
	return this->action_list.get_id();
}

colours::palette_e window_obj::WindowObj::get_colour_bg() {
	return this->drawing.get_colour();
}

void window_obj::WindowObj::save_data (iofile::File & savefile) {
	drawing.save_data(savefile);
	action_list.save_data(savefile);
}
