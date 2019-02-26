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

#include "log.h"
#include "graphics.h"
#include "menu.h"
#include "window_list.h"
#include "window_obj.h"

using namespace std;
using namespace log;
using namespace graphics;
using namespace menu;
using namespace window_list;
using namespace window_obj;

static WindowList * windows;

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


void graphics::test_graphics() {
	windows->add_node("test", 100, 50, 100, 50, menu_snake, menu_snake_items);

//	sleep(10);

	windows->add_node("test1", 300, 50, 500, 50, menu_snake, menu_snake_items);

	sleep(5);
}

void graphics::init_graphics(int argc, char** argv) {
	LOG_INFO(log::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );
	windows = new WindowList();

	test_graphics();

	glutMainLoop();
}

void graphics::display_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(log::verb_level_e::DEBUG,"[Display Callback] Display Callback for window ID: ", win_id);

	WindowObj window = windows->search_by_win_id(win_id);

	double win_width = 0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);

	double win_height = 0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);

	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

	unsigned char * bytes = new unsigned char[(int)win_width*(int)win_height];
	for (int wi=0; wi<(int)win_width;wi++) {
		for (int he=0; he<(int)win_height;he++) {
			bytes[wi+(int)win_height*he] = ((int)win_width + 2*win_id) % 16;
		}
	}

	glDrawPixels((int)win_width, (int)win_height, GL_RGB, GL_UNSIGNED_BYTE, bytes);

	delete [] bytes;

	// swap buffers to display the frame
	glutSwapBuffers();
}

void graphics::reshape_cb(int width, int height) {
	LOG_INFO(log::verb_level_e::DEBUG,"[Reshape Callback] Reshape Callback window width to ", width, " and window height to ", height);

	int win_id = 0;
	win_id = glutGetWindow();

	WindowObj window = windows->search_by_win_id(win_id);

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
void graphics::keyboard_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'n':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard callbak] Increase image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'p':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard callbak] Decrease image pointer because of pressing key ", key);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 'q':
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard callbak] Exit program because of pressing key ", key);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void graphics::specialkey_cb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard callbak] Increase image pointer because of pressing key Arrow Up");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(log::verb_level_e::DEBUG,"[Keyboard callbak] Decrease image pointer because of pressing key Arrow Down");
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
void graphics::mouse_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void graphics::idle_cb() {

	// force glut to call the display function
//	glutPostRedisplay();

}

void graphics::wrapper_cb() {
	LOG_INFO(log::verb_level_e::DEBUG,"[Graphics Wrapper] Enter graphics wrapper");
	glutDisplayFunc( display_cb );
	glutKeyboardFunc( keyboard_cb );
	glutReshapeFunc( reshape_cb );
	glutIdleFunc( idle_cb );
	glutSpecialFunc( specialkey_cb );
	glutMouseFunc( mouse_cb );
}
