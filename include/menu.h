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
	typedef enum snake_menu_list {
		RESTART,
		START_PAUSE,
		FASTER,
		SLOWER,
		QUIT
	} snake_menu_e;

	void menu_snake(menu::snake_menu_e entry);

	void menu_snake_items();

	template <typename entry_e>
	class Menu {
		public:
			// Constructor
			Menu(void (&EntryFunc)(entry_e) = nullptr, void (*ItemsFunc)() = nullptr): id(menu::Menu<entry_e>::create_menu(EntryFunc, ItemsFunc)) {
				std::string pretext ("Menu Constructor");
				menu::Menu<entry_e>::print_info(log::verb_level_e::LOW, pretext);
			}

			// Destructor
			~Menu();

		protected:
			int create_menu(void (*EntryFunc)(entry_e), void (*ItemsFunc)());
			void destroy_menu();
			void print_info(log::verb_level_e verbosity, std::string pretext);

		private:
			int id;
	};

	/** @} */ // End of MenuGroup group
}

template <typename entry_e>
int menu::Menu<entry_e>::create_menu(void (*EntryFunc)(entry_e), void (*ItemsFunc)()) {
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
#endif // MENU_H
