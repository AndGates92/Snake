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
void graphics_utils::win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)()) {
	windows->add_node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc);
}

void graphics_utils::refresh_window(int value) {

	window_node::WindowNode * head(windows->get_head());
	window_node::WindowNode * window_node (head);

	while (window_node != nullptr) {

		window_obj::WindowObj node = window_node->get_obj();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[Refresh window] Window ID: current ", curr_win_id);

		glutSetWindow(curr_win_id);
		glutPostRedisplay();

		window_node = window_node->get_next();

	}

	glutTimerFunc(value, graphics_utils::refresh_window, value);

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

void graphics_utils::reshape_cb(int width, int height) {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Reshape Callback] Reshape Callback window width to ", width, " and window height to ", height);

	int win_id = 0;
	win_id = glutGetWindow();

	window_node::WindowNode * node (graphics_utils::search_win_id(win_id));
	window_obj::WindowObj window (node->get_obj());

	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( graphics_utils::zoom, (GLdouble)width/(GLdouble)height, graphics_utils::zNear, graphics_utils::zFar );

//	glClear(GL_COLOR_BUFFER_BIT);

}
