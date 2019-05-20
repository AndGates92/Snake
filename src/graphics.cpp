/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 11th February 2019
 * @brief Graphics functions
 */

#include <string>
#include <iostream>
#include <fstream>

#include <unistd.h>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "shared_constants.h"
#include "colours.h"
#include "menu.h"
#include "logging.h"
#include "graphics.h"
#include "graphics_utils.h"
#include "game_graphics.h"
#include "stat_graphics.h"

using namespace std;
using namespace logging;
using namespace menu;
using namespace graphics;
using namespace graphics_utils;
using namespace game_graphics;

namespace {
	static int game_win_id;
	static int stat_win_id;
}

void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(logging::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );

	graphics::declare_game();

	if (argc == 1) {
		// Initialize graphics
		graphics::add_graphics();

		// Initialize game
		game_graphics::init_game();
	} else {

	}

	glutMainLoop();
}

void graphics::add_graphics() {
	std::string window_type ("Window");
	game_win_id = graphics_utils::win_node_add(shared_constants::game_win_title, window_type, 1100, 450, 100, 50, colours::palette_e::PURPLE);
	stat_win_id = graphics_utils::win_node_add(shared_constants::stat_win_title,  window_type, 200,  50, 1500, 50, colours::palette_e::BROWN);
}

void graphics::declare_game() {
	// Initialize settings
	snake_settings = settings::Settings();
	// Initialize window list
	graphics_utils::init_window_list();
	// Enable refresh timer
	graphics_utils::refresh_window(graphics_utils::refresh_timer_ms);
	// Initialize game
	game_graphics::declare_game_var();
}

void graphics::reshape_cb(int width, int height) {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Reshape Callback] Reshape Callback window width to ", width, " and window height to ", height);

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

void graphics::idle_cb() {

	window_list::WindowList * head_list(graphics_utils::get_window_ptr());
	window_node::WindowNode * head_node(head_list->get_head());
	window_node::WindowNode * window_node (head_node);

	while (window_node != nullptr) {

		int curr_win_id = window_node->get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Callback] Window ID: current ", curr_win_id);

		glutSetWindow(curr_win_id);

		if (curr_win_id == game_win_id) {
			game_graphics::idle_game_cb();
		} else if (curr_win_id == stat_win_id) {
			stat_graphics::idle_stat_cb();
		} else {
			LOG_ERROR("Unknown window ID: ", curr_win_id);
		}

		window_node = window_node->get_next();

	}

}
