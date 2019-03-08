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

#include <iostream>
#include "log.h"

using namespace std;
using namespace log;

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

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, menu::snake_menu_e menu_items)
	 *
	 * \param os: output stream
	 * \param menu_items: menu items in game window
	 *
	 * Overload << operator to print game menu items
	 */
	std::ostream& operator<< (std::ostream& os, menu::snake_menu_e menu_items);

	/**
	 * @brief Function: void menu_snake(int entry)
	 *
	 * \param entry: menu entry
	 *
	 * Select menu entry
	 */
	void menu_snake(int entry);

	/**
	 * @brief Function: void menu_snake_items()
	 *
	 * List menu items
	 */
	void menu_snake_items();

	class Menu {
		public:
			// Constructor
			Menu(void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): id(create_menu(EntryFunc, ItemsFunc)) {
				std::string pretext ("Menu Constructor");
				menu::Menu::print_info(log::verb_level_e::LOW, pretext);
			}

			Menu(const Menu& copy): id(copy.id) {};

			// Destructor
			~Menu();

			int get_id();
			void print_info(log::verb_level_e verbosity, std::string pretext);

			void destroy_menu();

		protected:
			int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)());

		private:
			int id;
	};

	/** @} */ // End of MenuGroup group
}

#endif // MENU_H
