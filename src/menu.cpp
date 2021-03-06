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

// ================================================================
// Create menu
// ================================================================
int menu::Menu::create_menu(void (*EntryFunc)(int), void (*ItemsFunc)()) {
	int menu_id;
	menu_id = glutCreateMenu(EntryFunc);
	ItemsFunc();

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu_id;
}

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
				settings::game_status_e game_status(snake_settings.get_game_status());

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

// Overload << operator for game_menu_e
std::ostream& menu::operator<< (std::ostream& os, const menu::game_menu_e & menu_items) {

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

// ================================================================
// Stat menu
// ================================================================
void menu::menu_stat(int entry) {
	switch (entry) {
		case static_cast<int>(menu::stat_menu_e::QUIT):
			LOG_INFO(logging::verb_level_e::ZERO,"[Menu stat] Close window");
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

void menu::menu_stat_items() {
	glutAddMenuEntry("Quit", static_cast<int>(menu::stat_menu_e::QUIT));
}

// Overload << operator for stat_menu_e
std::ostream& menu::operator<< (std::ostream& os, const menu::stat_menu_e & menu_items) {

	switch (menu_items) {
		case menu::stat_menu_e::QUIT:
			os << "QUIT";
			break;
		default:
			os << "Unknown menu item";
			break;
	}

	return os;
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
	LOG_INFO(logging::verb_level_e::DEBUG, "Destructor of menu ", this->title, " ID: ", this->id);
//	this->destroy_menu();
}

void menu::Menu::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] ", *this);
}

int menu::Menu::get_id() const {
	return id;
}

std::string menu::Menu::get_title() const {
	return title;
}

void menu::Menu::save_data (iofile::File & savefile) {
	savefile.write_ofile("Type: Menu\n");
	savefile.write_ofile("Title: ", this->title, "\n");
}

bool menu::Menu::operator== (const menu::Menu & rhs) {
	bool same_title = (this->title.compare(rhs.title) == 0);
	bool same_id = (this->id == rhs.id);
	return (same_title && same_id);
}

bool menu::Menu::operator!= (const menu::Menu & rhs) {
	bool different_title = (this->title.compare(rhs.title) != 0);
	bool different_id = (this->id != rhs.id);
	return (different_title && different_id);
}

std::ostream& menu::operator<< (std::ostream& os, const menu::Menu & win_menu) {
	os << "Menu Title " << win_menu.get_title() << " ID " << win_menu.get_id();
	return os;
}
