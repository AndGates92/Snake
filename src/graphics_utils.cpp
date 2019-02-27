/**
 * @copyright
 * @file graphics_utils.cpp
 * @author Andrea Gianarda
 * @date 27th February 2019
 * @brief Graphics utility functions
 */

#include <string>
#include <iostream>
#include <fstream>

#include "log.h"
#include "window_list.h"
#include "window_obj.h"
#include "graphics_utils.h"

using namespace std;
using namespace log;
using namespace window_list;
using namespace window_obj;
using namespace graphics_utils;

static window_list::WindowList * windows;

void graphics_utils::init_window_list() {
	windows = new WindowList();
}

void graphics_utils::delete_win_id(int& win_id) {
	windows->delete_by_win_id(win_id);
}

window_obj::WindowObj graphics_utils::search_win_id(int& win_id) {
	return windows->search_by_win_id(win_id);
}

void graphics_utils::delete_window() {
	int win_id = 0;
	win_id = glutGetWindow();

	graphics_utils::delete_win_id(win_id);
}


window_list::WindowList * & graphics_utils::get_window_ptr() {
	return windows;
}

void graphics_utils::win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)()) {
	graphics_utils::get_window_ptr()->add_node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc);
}
