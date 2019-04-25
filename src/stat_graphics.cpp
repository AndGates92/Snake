/**
 * @copyright
 * @file stat_graphics.cpp
 * @author Andrea Gianarda
 * @date 25th April 2019
 * @brief Stat graphics functions
 */

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "settings.h"
#include "logging.h"
#include "menu.h"
#include "graphics_utils.h"
#include "stat_graphics.h"
#include "window_obj.h"

using namespace std;
using namespace logging;
using namespace menu;
using namespace stat_graphics;
using namespace graphics_utils;
using namespace window_obj;

void stat_graphics::display_stat_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Display Stat Callback] Display Stat Callback for window ID: ", win_id);

//	double win_width = 0.0;
//	win_width = glutGet(GLUT_WINDOW_WIDTH);
//	int win_width_int = (int) win_width;

//	double win_height = 0.0;
//	win_height = glutGet(GLUT_WINDOW_HEIGHT);
//	int win_height_int = (int) win_height;

	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

	// swap buffers to display the frame
	glutSwapBuffers();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void stat_graphics::keyboard_stat_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Stat Callback] Exit program because of pressing key ", key);
			graphics_utils::delete_window();
			break;
		default:
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void stat_graphics::specialkey_stat_cb(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP:

			break;
		case GLUT_KEY_DOWN:

			break;
		case GLUT_KEY_LEFT:

			break;
		case GLUT_KEY_RIGHT:

			break;
		default:
			break;
	}
	// force glut to call the display function
	glutPostRedisplay();
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void stat_graphics::mouse_stat_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void stat_graphics::idle_stat_cb() {

//	int win_id = glutGetWindow();

//	int win_width = glutGet(GLUT_WINDOW_WIDTH);
//	int win_height = glutGet(GLUT_WINDOW_HEIGHT);

	int win_id_new = glutGetWindow();
	if (win_id_new != 0) {
		LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Stat Callback] Idle Stat Callback before glutPostRedisplay for window ID: ", win_id_new);
		// force glut to call the display function
		glutPostRedisplay();
	}

}

void stat_graphics::wrapper_stat_cb() {
	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Stat Graphics Wrapper] Enter stat graphics wrapper for window ID ", win_id);
	glutDisplayFunc( display_stat_cb );
	//glutDisplayFunc( display_stat_cb );
	glutKeyboardFunc( keyboard_stat_cb );
	glutReshapeFunc( graphics_utils::reshape_cb );
	//glutIdleFunc( idle_stat_cb );
	glutIdleFunc( NULL );
	glutSpecialFunc( specialkey_stat_cb );
	glutMouseFunc( mouse_stat_cb );
}

