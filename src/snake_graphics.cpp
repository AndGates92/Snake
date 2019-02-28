/**
 * @copyright
 * @file snake_graphics.cpp
 * @author Andrea Gianarda
 * @date 27th February 2019
 * @brief Snake graphics functions
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
#include "snake_graphics.h"
#include "window_obj.h"

using namespace std;
using namespace log;
using namespace menu;
using namespace snake_graphics;
using namespace graphics_utils;
using namespace window_obj;

/** @addtogroup SnakeGraphicsGroup
 *  @{
 */
/** @} */ // End of addtogroup SnakeGraphicsGroup

void snake_graphics::display_snake_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(log::verb_level_e::DEBUG,"[Display Snake Callback] Display Snake Callback for window ID: ", win_id);
cout << "[Display Snake Callback] Display Snake Callback for window ID: " << win_id << endl;

	window_obj::WindowObj window = graphics_utils::search_win_id(win_id);

	double win_width = 0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);

	double win_height = 0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);

	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

	char * pixels = get_pixel_array<char>((int)win_width, (int)win_height);

	glDrawPixels((int)win_width, (int)win_height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	delete [] pixels;

	// swap buffers to display the frame
	glutSwapBuffers();
}

void snake_graphics::reshape_snake_cb(int width, int height) {
	LOG_INFO(log::verb_level_e::DEBUG,"[Reshape Snake Callback] Reshape Snake Callback window width to ", width, " and window height to ", height);
cout << "[Reshape Snake Callback] Reshape Snake Callback window width to " << width << " and window height to " << height << endl;

	int win_id = 0;
	win_id = glutGetWindow();

	window_obj::WindowObj window = graphics_utils::search_win_id(win_id);

	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( snake_graphics::zoom, (GLdouble)width/(GLdouble)height, snake_graphics::zNear, snake_graphics::zFar );

//	glClear(GL_COLOR_BUFFER_BIT);

}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void snake_graphics::keyboard_snake_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'n':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Snake Callback] Increase image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'p':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Snake Callback] Decrease image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'q':
			graphics_utils::delete_window();
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Snake Callback] Exit program because of pressing key ", key);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void snake_graphics::specialkey_snake_cb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Snake Callback] Increase image pointer because of pressing key Arrow Up");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard Snake Callback] Decrease image pointer because of pressing key Arrow Down");
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
void snake_graphics::mouse_snake_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void snake_graphics::idle_snake_cb() {

	// force glut to call the display function
//	glutPostRedisplay();

}

void snake_graphics::wrapper_snake_cb() {
	LOG_INFO(log::verb_level_e::DEBUG,"[Snake Graphics Wrapper] Enter snake graphics wrapper");
cout << "[Snake Graphics Wrapper] Enter snake graphics wrapper" << endl;
	glutDisplayFunc( display_snake_cb );
	glutKeyboardFunc( keyboard_snake_cb );
	glutReshapeFunc( reshape_snake_cb );
	glutIdleFunc( idle_snake_cb );
	glutSpecialFunc( specialkey_snake_cb );
	glutMouseFunc( mouse_snake_cb );
}
