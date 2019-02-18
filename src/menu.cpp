/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 06th February 2019
 * @brief Menu function
 */

#include <iostream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "menu.h"
#include "log.h"

using namespace std;
using namespace menu;
using namespace log;

// ================================================================
// Snake menu
// ================================================================
void menu::menu_snake(int entry) {
	switch (entry) {
		case static_cast<int>(menu::snake_menu_e::RESTART):
			LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Restart game");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::snake_menu_e::START_PAUSE):
			LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Start/Pause snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::snake_menu_e::FASTER):
			LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Increease speed of snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::snake_menu_e::SLOWER):
			LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Decrease speed of snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::snake_menu_e::QUIT):
			LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Close window and exits program");
			exit(EXIT_SUCCESS);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

void menu::menu_snake_items() {
	glutAddMenuEntry("Restart", static_cast<int>(menu::snake_menu_e::RESTART));
	glutAddMenuEntry("Start/Pause", static_cast<int>(menu::snake_menu_e::START_PAUSE));
	glutAddMenuEntry("Faster", static_cast<int>(menu::snake_menu_e::FASTER));
	glutAddMenuEntry("Slower", static_cast<int>(menu::snake_menu_e::SLOWER));
	glutAddMenuEntry("Quit", static_cast<int>(menu::snake_menu_e::QUIT));
}


