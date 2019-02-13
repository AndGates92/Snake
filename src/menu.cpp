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
void menu::menu_snake(menu::snake_menu_e entry) {
	switch (entry) {
		case menu::snake_menu_e::RESTART:
			log::LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Restart game");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case menu::snake_menu_e::START_PAUSE:
			log::LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Start/Pause snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case menu::snake_menu_e::FASTER:
			log::LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Increease speed of snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case menu::snake_menu_e::SLOWER:
			log::LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Decrease speed of snake");
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case menu::snake_menu_e::QUIT:
			log::LOG_INFO(log::verb_level_e::ZERO,"[Menu snake] Close window and exits program");
			exit(EXIT_SUCCESS);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

void menu::menu_snake_items() {
	glutAddMenuEntry("Restart", menu::snake_menu_e::RESTART);
	glutAddMenuEntry("Start/Pause", menu::snake_menu_e::START_PAUSE);
	glutAddMenuEntry("Faster", menu::snake_menu_e::FASTER);
	glutAddMenuEntry("Slower", menu::snake_menu_e::SLOWER);
	glutAddMenuEntry("Quit", menu::snake_menu_e::QUIT);
}

// ================================================================
// Destroy window
// ================================================================

void menu::Menu::destroy_menu() {
	glutDestroyMenu(id);
}

// ================================================================
// Destructor
// ================================================================
menu::Menu::~Menu() {
	menu::Menu::destroy_menu();
}
