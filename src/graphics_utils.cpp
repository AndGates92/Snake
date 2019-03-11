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

#include "logging.h"
#include "window_list.h"
#include "window_obj.h"
#include "graphics_utils.h"

using namespace std;
using namespace logging;
using namespace window_list;
using namespace window_obj;
using namespace graphics_utils;

namespace {
	static window_list::WindowList * windows;
}

void graphics_utils::init_window_list() {
	windows = new window_list::WindowList();
}

// Delete window having the ID passed as input
void graphics_utils::delete_win_id(int& win_id) {
	windows->delete_by_win_id(win_id);
}

// Search window having the ID passed as input
window_node::WindowNode * graphics_utils::search_win_id(int& win_id) {
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

// Create new window
void graphics_utils::win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)()) {
	windows->add_node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc);
}

// Overload << operator for palette_e
std::ostream& graphics_utils::operator<< (std::ostream& os, graphics_utils::palette_e palette) {

	switch (palette) {
		case graphics_utils::palette_e::RED:
			os << "RED";
			break;
		case graphics_utils::palette_e::BLUE:
			os << "BLUE";
			break;
		case graphics_utils::palette_e::GREEN:
			os << "GREEN";
			break;
		case graphics_utils::palette_e::YELLOW:
			os << "YELLOW";
			break;
		case graphics_utils::palette_e::PURPLE:
			os << "PURPLE";
			break;
		case graphics_utils::palette_e::PINK:
			os << "PINK";
			break;
		case graphics_utils::palette_e::BROWN:
			os << "BROWN";
			break;
		case graphics_utils::palette_e::WHITE:
			os << "WHITE";
			break;
		case graphics_utils::palette_e::BLACK:
			os << "BLACK";
			break;
		default:
			os << "Unknown colour";
			break;
	}

	return os;
}
