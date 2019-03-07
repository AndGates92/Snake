/**
 * @copyright
 * @file game_graphics.cpp
 * @author Andrea Gianarda
 * @date 27th February 2019
 * @brief Game graphics functions
 */

#include <string>
#include <iostream>
#include <fstream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"
#include "menu.h"
#include "graphics_utils.h"
#include "game_graphics.h"
#include "window_obj.h"
#include "snake_list.h"
#include "snake_node.h"

using namespace std;
using namespace log;
using namespace menu;
using namespace game_graphics;
using namespace graphics_utils;
using namespace window_obj;
using namespace snake_list;
using namespace snake_node;

void game_graphics::display_game_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(log::verb_level_e::DEBUG,"[Display Game Callback] Display Game Callback for window ID: ", win_id);

	window_node::WindowNode * node = graphics_utils::search_win_id(win_id);
	window_obj::WindowObj window = node->get_obj();

	double win_width = 0.0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	int win_width_int = (int) win_width;

	double win_height = 0.0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);
	int win_height_int = (int) win_height;


	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

	// Store pixels in pixels array
	unsigned char * pixels = game_graphics::get_game_pixel_array<unsigned char>(win_width_int, win_height_int);

	glDrawPixels(win_width_int, win_height_int, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	delete [] pixels;

	// swap buffers to display the frame
	glutSwapBuffers();
}

void game_graphics::reshape_game_cb(int width, int height) {
	LOG_INFO(log::verb_level_e::DEBUG,"[Reshape Game Callback] Reshape Game Callback window width to ", width, " and window height to ", height);

	int win_id = 0;
	win_id = glutGetWindow();

	window_node::WindowNode * node = graphics_utils::search_win_id(win_id);
	window_obj::WindowObj window = node->get_obj();

	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( game_graphics::zoom, (GLdouble)width/(GLdouble)height, game_graphics::zNear, game_graphics::zFar );

//	glClear(GL_COLOR_BUFFER_BIT);

}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::keyboard_game_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'n':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Game Callback] Increase image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'p':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Game Callback] Decrease image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'q':
			graphics_utils::delete_window();
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Game Callback] Exit program because of pressing key ", key);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::specialkey_game_cb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Game Callback] Increase image pointer because of pressing key Arrow Up");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Game Callback] Decrease image pointer because of pressing key Arrow Down");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		default:
			glutPostRedisplay();
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::mouse_game_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void game_graphics::idle_game_cb() {

	// force glut to call the display function
//	glutPostRedisplay();

}

void game_graphics::wrapper_game_cb() {
	LOG_INFO(log::verb_level_e::DEBUG,"[Game Graphics Wrapper] Enter game graphics wrapper");
	glutDisplayFunc( display_game_cb );
	glutKeyboardFunc( keyboard_game_cb );
	glutReshapeFunc( reshape_game_cb );
	glutIdleFunc( idle_game_cb );
	glutSpecialFunc( specialkey_game_cb );
	glutMouseFunc( mouse_game_cb );
}


void game_graphics::init_snake_list() {
	game_graphics::snake = new snake_list::SnakeList();
}

snake_list::SnakeList * & game_graphics::get_snake_ptr() {
	return snake;
}

void game_graphics::populate_snake_list() {
	int centre_x = 10;
	int centre_y = 10;
	for (int unit_no=0; unit_no < game_graphics::init_units; unit_no++) {

		game_graphics::snake->add_node(centre_x, centre_y, snake_node_width, snake_node_height, snake_node::direction_e::RIGHT, graphics_utils::palette_e::RED);

		centre_x += snake_node_width;

	}

}
