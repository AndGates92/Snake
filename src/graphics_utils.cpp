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

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "colours.h"
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
	windows = new window_list::WindowList("Window");
	if (windows == nullptr) {
		LOG_ERROR("Can't allocate memory for window list");
	}
}

// Delete window having the ID passed as input
void graphics_utils::delete_win_id(int& win_id) {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Delete window ID] Delete window with ID: ", win_id);
	windows->delete_by_win_id(win_id);
}

// Search window having the ID passed as input
window_node::WindowNode * graphics_utils::search_win_id(int& win_id) {
	return windows->search_by_win_id(win_id);
}

void graphics_utils::delete_window() {
	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Delete window] Delete window with ID: ", win_id);

	graphics_utils::delete_win_id(win_id);
}

void graphics_utils::delete_all_windows() {
	windows->~WindowList();
//	delete windows;
}

window_list::WindowList * & graphics_utils::get_window_ptr() {
	return windows;
}

// Create new window
int graphics_utils::win_node_add(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour) {
	int win_id = windows->add_node(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour);
	return win_id;
}

void graphics_utils::refresh_window(int value) {

	window_node::WindowNode * head(windows->get_head());
	window_node::WindowNode * window_node (head);

	while (window_node != nullptr) {

		int curr_win_id = window_node->get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[Refresh window] Window ID: current ", curr_win_id);

		glutSetWindow(curr_win_id);
		glutPostRedisplay();

		window_node = window_node->get_next();

	}

	glutTimerFunc(value, graphics_utils::refresh_window, value);

}


void graphics_utils::save_window(iofile::File & savefile) {

	int win_node_cnt = 0;

	window_node::WindowNode * curr_win_node(windows->get_head());

	while (curr_win_node != nullptr) {
		savefile.write_ofile("//******************************\n");
		savefile.write_ofile("// Window ", win_node_cnt, "\n");
		savefile.write_ofile("//******************************\n");
		curr_win_node->save_data(savefile);

		savefile.write_ofile("\n");

		// Save temporary obstacle
		curr_win_node = curr_win_node->get_next();
		win_node_cnt++;
	}

}
