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
#include <exception>

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

	char * win_name = nullptr;
	// Create window
	try {
		win_name = new char [WIN_NAME_LENGTH_MAX];
	} catch (std::exception& alloc_e) {
		LOG_ERROR("Caught exception ", alloc_e.what(), " when allocating memory for window name");
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
	LOG_INFO(verbosity, "[", pretext, "] ", this);
}

int window::Window::get_id() const {
	return this->id;
}

std::string window::Window::get_title() const {
	return this->title;
}

void window::Window::save_data (iofile::File & savefile) {
	basic_object::BasicObject::save_data(savefile);
	savefile.write_ofile("Title: ", this->title, "\n");
	savefile.write_ofile("\n");
}

bool window::Window::operator== (const window::Window & rhs) {
	bool same_title = (this->title.compare(rhs.title) == 0);
	bool same_id = (this->id == rhs.id);
	return (same_title && same_id && (static_cast<basic_object::BasicObject>(*this) == static_cast<basic_object::BasicObject>(rhs)));
}

bool window::Window::operator!= (const window::Window & rhs) {
	bool different_title = (this->title.compare(rhs.title) != 0);
	bool different_id = (this->id != rhs.id);
	return (different_title && different_id && (static_cast<basic_object::BasicObject>(*this) != static_cast<basic_object::BasicObject>(rhs)));
}

std::ostream& operator<< (std::ostream& os, const window::Window & win) {
	basic_object::BasicObject basic_obj(static_cast<const basic_object::BasicObject &>(win));

	os << basic_obj << " Title " << win.get_title() << " ID " << win.get_id();

	return os;
}
