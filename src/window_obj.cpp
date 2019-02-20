/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief File function
 */

#include <iostream>

#include "window_obj.h"
#include "log.h"

using namespace std;
using namespace log;
using namespace window_obj;


window_obj::WindowObj::~WindowObj() {
	std::string pretext ("Window Object Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
	this->drawing.~Window();
	this->action_list.~Menu();
}

void window_obj::WindowObj::print_info(log::verb_level_e verbosity, std::string pretext) {
	this->drawing.print_info(verbosity, pretext);
	this->action_list.print_info(verbosity, pretext);
}

int window_obj::WindowObj::get_win_id() {
	return this->drawing.get_id();
}

int window_obj::WindowObj::get_menu_id() {
	return this->action_list.get_id();
}
