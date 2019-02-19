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

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"
#include "graphics.h"
#include "menu.h"
#include "window_list.h"

using namespace std;
using namespace log;
using namespace graphics;
using namespace menu;
using namespace window_list;
using namespace window_node;

WindowList * windows;

/** @addtogroup GraphicsGroup
 *  @{
 */
/**
 * @brief FIeld of view
 *
 */
static GLfloat zoom = 50.0;

/**
 * @brief Near clip
 *
 */
static GLfloat zNear = 1.0;

/**
 * @brief Far clip
 *
 */
static GLfloat zFar = 1.0;

/** @} */ // End of addtogroup GraphicsGroup


void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(log::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );
	windows = new WindowList;

	windows->add_node("test", 50, 50, 50, 50, menu_snake, menu_snake_items);
}

void graphics::display_dataset_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

//	int win_id = 0;
//	win_id = glutGetWindow();

	LOG_INFO(log::verb_level_e::DEBUG,"[Display cb] Display cb");

//	WindowNode * window = NULL;
//	window = windows->search_by_win_id(win_id);

	double win_width = 0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);

	double win_height = 0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);

	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels((int)win_width, (int)win_height, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// swap buffers to display the frame
	glutSwapBuffers();
}

void graphics::reshape_dataset_cb(int width, int height) {
	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( zoom, (GLdouble)width/(GLdouble)height, zNear, zFar );

//	glClear(GL_COLOR_BUFFER_BIT);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void graphics::keyboard_dataset_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'n':
			LOG_INFO(log::verb_level_e::ZERO,"[Keyboard callbak] Increase image pointer because of pressing key %c", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'p':
			LOG_INFO(log::verb_level_e::ZERO,"[Keyboard callbak] Decrease image pointer because of pressing key %c", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'q':
			LOG_INFO(log::verb_level_e::ZERO,"[Keyboard callbak] Exit program because of pressing key %c", key);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void graphics::specialkey_dataset_cb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(log::verb_level_e::ZERO,"[Keyboard callbak] Increase image pointer because of pressing key Arrow Up");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(log::verb_level_e::ZERO,"[Keyboard callbak] Decrease image pointer because of pressing key Arrow Down");
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
void graphics::mouse_dataset_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void graphics::idle_dataset_cb() {

	// force glut to call the display function
	//glutPostRedisplay();

}

void graphics::wrapper_dataset_cb() {
	glutDisplayFunc( display_dataset_cb );
	glutKeyboardFunc( keyboard_dataset_cb );
	glutReshapeFunc( reshape_dataset_cb );
	glutIdleFunc( idle_dataset_cb );
	glutSpecialFunc( specialkey_dataset_cb );
	glutMouseFunc( mouse_dataset_cb );
}
