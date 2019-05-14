/**
 * @copyright
 * @file file.cpp
 * @author Andrea Gianarda
 * @date 06th February 2019
 * @brief File function
 */

#include <map>
#include <string>
#include <cstring>
#include <iostream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "shared_constants.h"
#include "colours.h"
#include "graphics.h"
#include "window.h"
#include "logging.h"
#include "basic_object.h"
#include "game_graphics.h"
#include "stat_graphics.h"

using namespace std;
using namespace window;
using namespace logging;
using namespace graphics;

#define __STD_WANT_LIB_EXT1__ 1

namespace window {
	typedef void (*WrapperFuncPtr)(void);

	namespace {
		static std::map <std::string, WrapperFuncPtr> WrapperFunc = {
			{ shared_constants::game_win_title, game_graphics::wrapper_game_cb},
			{ shared_constants::stat_win_title, stat_graphics::wrapper_stat_cb}
		};
	}
}

// ================================================================
// Destructor
// ================================================================
window::Window::~Window() {
	std::string pretext ("Window Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

// ================================================================
// Create window
// ================================================================
int window::Window::create_window(std::string title, int width, int height, int xpos, int ypos) {
	LOG_INFO(logging::verb_level_e::HIGH, "[Create window] Create window at ", xpos, ", ", ypos, ". Dimensions: width ", width, " height ", height, ". Title: ", title);
	ASSERT(width > 0)
	ASSERT(height > 0)
	glutInitWindowSize(width, height);
	glutInitWindowPosition(xpos, ypos);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// Create window
	char * win_name = new char [WIN_NAME_LENGTH_MAX];
	if (win_name == nullptr) {
		LOG_ERROR("Can't allocate memory for window name");
	}
	ASSERT(title.length() < WIN_NAME_LENGTH_MAX)

	std::strcpy(win_name, title.c_str());

	int win_id = 0;
	win_id = glutCreateWindow(win_name);

	delete [] win_name;

	window::WrapperFunc[title]();

	return win_id;
}

void window::Window::destroy_window() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Destroy Window");
	glutDestroyWindow(this->id);
}

void window::Window::print_info(logging::verb_level_e verbosity, std::string pretext) {
	basic_object::BasicObject::print_info(verbosity, pretext);
	std::string type = this->get_type();
	LOG_INFO(verbosity, "[", pretext, "] ", type, " with ID ", this->id, " Title: ", this->title);
}

int window::Window::get_id() {
	return this->id;
}
