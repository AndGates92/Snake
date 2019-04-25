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

using namespace std;
using namespace logging;
using namespace menu;
using namespace graphics;
using namespace graphics_utils;
using namespace game_graphics;

void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(logging::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );

	graphics::start_game();

	glutMainLoop();
}

void graphics::add_graphics() {
	graphics_utils::win_node_add("snake", 1100, 450, 100, 50, menu::menu_game, menu::menu_game_items, game_graphics::wrapper_game_cb);

}

void graphics::start_game() {
	// Initialize settings
	snake_settings = settings::Settings();
	// Initialize window list
	graphics_utils::init_window_list();
	// Initialize graphics
	graphics::add_graphics();
	// Initialize game
	game_graphics::init_game();
}
