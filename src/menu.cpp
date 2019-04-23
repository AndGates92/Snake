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
#include "logging.h"
#include "settings.h"

using namespace std;
using namespace menu;
using namespace logging;

// ================================================================
// Snake menu
// ================================================================
void menu::menu_game(int entry) {
	switch (entry) {
		case static_cast<int>(menu::game_menu_e::RESTART):
			snake_settings.set_game_status(settings::game_status_e::RESTART);
			break;
		case static_cast<int>(menu::game_menu_e::START_PAUSE):
			LOG_INFO(logging::verb_level_e::ZERO,"[Menu snake] Start/Pause snake");
			// Explicitely limit scope of variable game_status
			{
				settings::game_status_e game_status = snake_settings.get_game_status();

				if (game_status == settings::game_status_e::RUNNING) {
					snake_settings.set_game_status(settings::game_status_e::PAUSED);
				} else if (game_status == settings::game_status_e::PAUSED) {
					snake_settings.set_game_status(settings::game_status_e::RUNNING);
				}
				LOG_INFO(logging::verb_level_e::DEBUG,"[Menu snake] Game state: ", snake_settings.get_game_status());
			}
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::game_menu_e::FASTER):
			LOG_INFO(logging::verb_level_e::ZERO,"[Menu snake] Increease speed of snake");
			// Explicitely limit scope of variable speed and speed_incr
			{
				int speed = snake_settings.get_speed();
				int speed_incr = snake_settings.get_speed_incr();
				LOG_INFO(logging::verb_level_e::DEBUG,"[Menu Snake] Speed up snake to ", speed);
				snake_settings.set_speed(speed + speed_incr);
			}
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::game_menu_e::SLOWER):
			LOG_INFO(logging::verb_level_e::ZERO,"[Menu snake] Decrease speed of snake");
			// Explicitely limit scope of variable speed and speed_incr
			{
				int speed = snake_settings.get_speed();
				int speed_incr = snake_settings.get_speed_incr();

				if (speed > speed_incr) {
					snake_settings.set_speed(speed - speed_incr);
				}
				LOG_INFO(logging::verb_level_e::DEBUG,"[Menu Snake] Slow down snake to ", speed);
				ASSERT(snake_settings.get_speed() > 0)
				// force glut to call the display function
			}
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case static_cast<int>(menu::game_menu_e::QUIT):
			LOG_INFO(logging::verb_level_e::ZERO,"[Menu snake] Close window and exits program");
			snake_settings.set_game_status(settings::game_status_e::EXIT);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

void menu::menu_game_items() {
	glutAddMenuEntry("Restart", static_cast<int>(menu::game_menu_e::RESTART));
	glutAddMenuEntry("Start/Pause", static_cast<int>(menu::game_menu_e::START_PAUSE));
	glutAddMenuEntry("Faster", static_cast<int>(menu::game_menu_e::FASTER));
	glutAddMenuEntry("Slower", static_cast<int>(menu::game_menu_e::SLOWER));
	glutAddMenuEntry("Quit", static_cast<int>(menu::game_menu_e::QUIT));
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
	LOG_INFO(logging::verb_level_e::DEBUG, "Destroy Menu");
	glutDestroyMenu(id);
}

// ================================================================
// Destructor
// ================================================================
menu::Menu::~Menu() {
	std::string pretext ("Menu Destructor");
	menu::Menu::print_info(logging::verb_level_e::LOW, pretext);
//	this->destroy_menu();
}

void menu::Menu::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Menu ID: ", this->id);
}

int menu::Menu::get_id() {
	return id;
}

// Overload << operator for game_menu_e
std::ostream& menu::operator<< (std::ostream& os, menu::game_menu_e menu_items) {

	switch (menu_items) {
		case menu::game_menu_e::RESTART:
			os << "RESTART";
			break;
		case menu::game_menu_e::START_PAUSE:
			os << "START/PAUSE";
			break;
		case menu::game_menu_e::FASTER:
			os << "FASTER";
			break;
		case menu::game_menu_e::SLOWER:
			os << "SLOWER";
			break;
		case menu::game_menu_e::QUIT:
			os << "QUIT";
			break;
		default:
			os << "Unknown menu item";
			break;
	}

	return os;
}
