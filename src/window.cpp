/**
 * @copyright
 * @file file.cpp
 * @author Andrea Gianarda
 * @date 06th February 2019
 * @brief File function
 */

#include <string>
#include <cstring>
#include <iostream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "window.h"
#include "log.h"

using namespace std;
using namespace window;
using namespace log;
using namespace graphics;

#define __STD_WANT_LIB_EXT1__ 1

// ================================================================
// Destructor
// ================================================================
window::Window::~Window() {
	std::string pretext ("Window Destructor");
	window::Window::print_info(log::verb_level_e::LOW, pretext);
	window::Window::destroy_window();
}

// ================================================================
// Create window
// ================================================================
int window::Window::create_window(std::string title, int width, int height, int xpos, int ypos) {
	LOG_INFO(log::verb_level_e::HIGH, "[Create window] Create window at ", xpos, ", ", ypos, ". Dimensions: width ", width, " height ", height, ". Title: ", title);
	ASSERT(width > 0)
	ASSERT(height > 0)
	glutInitWindowSize(width, height);
	glutInitWindowPosition(xpos, ypos);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	char * win_name = new char [WIN_NAME_LENGTH_MAX];
//	ASSERT(title.length() < WIN_NAME_LENGTH_MAX);

	//std::strcpy_s(win_name, WIN_NAME_LENGTH_MAX, title.c_str());
	std::strcpy(win_name, title.c_str());

	int win_id = 0;
	win_id = glutCreateWindow(win_name);

	wrapper_dataset_cb();

	return win_id;
}

void window::Window::destroy_window() {
	glutDestroyWindow(id);
}

void window::Window::print_info(log::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Window ID ", id, " at ", pos_x, ", ", pos_y, ". Dimensions: width ", width, " height ", height, ". Title: ", title);
}

int window::Window::get_id() {
	return id;
}
