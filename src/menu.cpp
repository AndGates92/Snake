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

int menu::Menu::create_menu(void (*EntryFunc)(int), void (*ItemsFunc)()) {
	int menu_id;
	menu_id = glutCreateMenu(EntryFunc);
	ItemsFunc();

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu_id;
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
	std::string pretext ("Menu Destructor");
	print_info(log::verb_level_e::LOW, pretext);
	destroy_menu();
}

void menu::Menu::print_info(log::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Menu ID ", id);
}

int menu::Menu::get_id() {
	return id;
}
