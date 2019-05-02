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

	graphics::start_game();

	glutMainLoop();
}

void graphics::add_graphics() {
	game_win_id = graphics_utils::win_node_add("snake", 1100, 450, 100, 50, menu::menu_game, menu::menu_game_items, game_graphics::wrapper_game_cb);
	stat_win_id = graphics_utils::win_node_add("stat",  200,  50, 1500, 50, menu::menu_stat, menu::menu_stat_items, stat_graphics::wrapper_stat_cb);
}

void graphics::start_game() {
	// Initialize settings
	snake_settings = settings::Settings();
	// Initialize window list
	graphics_utils::init_window_list();
	// Initialize graphics
	graphics::add_graphics();
	// Enable refresh timer
	graphics_utils::refresh_window(graphics_utils::refresh_timer_ms);
	// Initialize game
	game_graphics::init_game();
}

void graphics::reshape_cb(int width, int height) {
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

void graphics::idle_cb() {

	window_list::WindowList * head_list(graphics_utils::get_window_ptr());
	window_node::WindowNode * head_node(head_list->get_head());
	window_node::WindowNode * window_node (head_node);

	while (window_node != nullptr) {

		window_obj::WindowObj node = window_node->get_obj();
		int curr_win_id = node.get_win_id();

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
