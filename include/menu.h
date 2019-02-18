#ifndef MENU_H
#define MENU_H
/**
 * @copyright
 * @file menu.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Menu header file
*/

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"

namespace menu {
	/** @defgroup MenuGroup Menu Doxygen Group
	 *  Menu functions and classes
	 *  @{
	 */
	/**
	 * @brief Snake menu entries
	 *
	 */
	typedef enum class snake_menu_list {
		RESTART = 0,
		START_PAUSE = 1,
		FASTER = 2,
		SLOWER = 3,
		QUIT = 4
	} snake_menu_e;

	void menu_snake(int entry);

	void menu_snake_items();

	template <typename entry_e>
	class Menu {
		public:
			// Constructor
			Menu(void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): id(create_menu(EntryFunc, ItemsFunc)) {
				std::string pretext ("Menu Constructor");
				menu::Menu<entry_e>::print_info(log::verb_level_e::LOW, pretext);
			}

			Menu(const Menu& copy): id(copy.id) {};

			// Destructor
			~Menu();

			int get_id();

		protected:
			int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)());
			void destroy_menu();
			void print_info(log::verb_level_e verbosity, std::string pretext);

		private:
			int id;
	};

	/** @} */ // End of MenuGroup group
}

template <typename entry_e>
int menu::Menu<entry_e>::create_menu(void (*EntryFunc)(int), void (*ItemsFunc)()) {
	int menu_id;
	menu_id = glutCreateMenu(EntryFunc);
	ItemsFunc();

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu_id;
}

// ================================================================
// Destroy window
// ================================================================

template <typename entry_e>
void menu::Menu<entry_e>::destroy_menu() {
	glutDestroyMenu(id);
}

// ================================================================
// Destructor
// ================================================================
template <typename entry_e>
menu::Menu<entry_e>::~Menu() {
	std::string pretext ("Menu Destructor");
	menu::Menu<entry_e>::print_info(log::verb_level_e::LOW, pretext);
	menu::Menu<entry_e>::destroy_menu();
}

template <typename entry_e>
void menu::Menu<entry_e>::print_info(log::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Menu ID ", id);
}

template <typename entry_e>
int menu::Menu<entry_e>::get_id() {
	return id;
}
#endif // MENU_H
