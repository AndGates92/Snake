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
#include "log.h"
#include "graphics.h"
#include "graphics_utils.h"
#include "game_graphics.h"

using namespace std;
using namespace log;
using namespace menu;
using namespace graphics;
using namespace graphics_utils;
using namespace game_graphics;

void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(log::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );

	// Initialize window list
	graphics_utils::init_window_list();

	game_graphics::init_snake_list();

	graphics::test_graphics();

	glutMainLoop();
}

void graphics::test_graphics() {
	graphics_utils::win_node_add("test", 1100, 450, 100, 50, menu::menu_snake, menu::menu_snake_items, game_graphics::wrapper_game_cb);

	game_graphics::populate_snake_list();
//	sleep(10);

	graphics_utils::win_node_add("test1", 1300, 350, 500, 50, menu::menu_snake, menu::menu_snake_items, game_graphics::wrapper_game_cb);

	sleep(5);
}
