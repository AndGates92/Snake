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
	window_obj::WindowObj::drawing.~Window();
	window_obj::WindowObj::action_list.~Menu();
}

void window_obj::WindowObj::print_info(log::verb_level_e verbosity, std::string pretext) {
	window_obj::WindowObj::drawing.print_info(verbosity, pretext);
	window_obj::WindowObj::action_list.print_info(verbosity, pretext);
}

int window_obj::WindowObj::get_win_id() {
	return drawing.get_id();
}

int window_obj::WindowObj::get_menu_id() {
	return action_list.get_id();
}
