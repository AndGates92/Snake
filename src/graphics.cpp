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
#include <vector>

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
#include "game_utils.h"
#include "stat_graphics.h"
#include "cmdline_parser.h"

using namespace std;
using namespace logging;
using namespace menu;
using namespace graphics;
using namespace graphics_utils;
using namespace game_graphics;
using namespace game_utils;
using namespace cmdline_parser;

/** @addtogroup GraphicsGroup
 *
 *  @{
 */
namespace graphics {
	namespace {
		/**
		 * @brief game window ID
		 *
		 */
		static int game_win_id;
		/**
		 * @brief statistics window ID
		 *
		 */
		static int stat_win_id;
	}
}
/** @} */ // End of addtogroup GraphicsGroup

void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(logging::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );

	// Initialize window list
	graphics_utils::init_window_list();

	graphics::declare_game();

	bool input_file_found = cmdline_parser::parse(argc, argv);

	if (input_file_found == true) {
		// Process input file passed through command line
		cmdline_parser::process();
	} else {
		// Initialize graphics (windows)
		graphics::add_graphics();

		// Initialize game
		game_utils::init_game();
	}

	// Initialize game parameters
	game_utils::init_game_parameters();

	glutMainLoop();
}

void graphics::add_graphics() {
	std::string window_type ("Window");
	game_win_id = graphics_utils::win_node_add(shared_constants::game_win_title, window_type, shared_constants::game_win_width, shared_constants::game_win_height, shared_constants::game_win_pos_x, shared_constants::game_win_pos_y, shared_constants::game_win_bg);
	stat_win_id = graphics_utils::win_node_add(shared_constants::stat_win_title, window_type, shared_constants::stat_win_width, shared_constants::stat_win_height, shared_constants::stat_win_pos_x, shared_constants::stat_win_pos_y, shared_constants::stat_win_bg);
}

void graphics::declare_game() {
	// Initialize settings
	snake_settings = settings::Settings();
	// Enable refresh timer
	graphics_utils::refresh_window(graphics_utils::refresh_timer_ms);
	// Initialize game
	game_utils::declare_game_var();
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

	window_list::WindowList &  head_list = graphics_utils::get_window_ptr();
	std::vector<window_obj::WindowObj> & window = head_list.get_head();

	for (auto && node : window) {

		int curr_win_id = node.get_win_id();
		std::string curr_win_title = node.get_win_title();

		LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Callback] Window ID: ", curr_win_id, " Title: ", curr_win_title);

		glutSetWindow(curr_win_id);

		//if (curr_win_title == shared_constants::game_win_title) {
		if (curr_win_id == game_win_id) {
			game_graphics::idle_game_cb();
		//} else if (curr_win_title == shared_constants::stat_win_title) {
		} else if (curr_win_id == stat_win_id) {
			stat_graphics::idle_stat_cb();
		} else {
			LOG_ERROR("Unknown window ID: ", curr_win_id, " Title: ", curr_win_title);
		}

	}

}

void graphics::set_id(int id, std::string type) {

	if (type.compare(shared_constants::stat_win_title) == 0) {
		stat_win_id = id;
	} else if (type.compare(shared_constants::game_win_title) == 0) {
		game_win_id = id;
	} else {
		LOG_ERROR("Unknown window type: ", type);
	}
}
