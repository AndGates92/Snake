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
#include "logging.h"

using namespace std;
using namespace logging;

namespace menu {
	/** @defgroup MenuGroup Menu Doxygen Group
	 *  Menu functions and classes
	 *  @{
	 */
	/**
	 * @brief Snake menu entries
	 *
	 */
	typedef enum class game_menu_list {
		RESTART = 0,
		START_PAUSE = 1,
		FASTER = 2,
		SLOWER = 3,
		QUIT = 4
	} game_menu_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, menu::game_menu_e menu_items)
	 *
	 * \param os: output stream
	 * \param menu_items: menu items in game window
	 *
	 * Overload << operator to print game menu items
	 */
	std::ostream& operator<< (std::ostream& os, menu::game_menu_e menu_items);

	/**
	 * @brief Function: void menu_game(int entry)
	 *
	 * \param entry: menu entry
	 *
	 * Select menu entry in game window
	 */
	void menu_game(int entry);

	/**
	 * @brief Function: void menu_game_items()
	 *
	 * List menu items in game window
	 */
	void menu_game_items();

	/**
	 * @brief Stat menu entries
	 *
	 */
	typedef enum class stat_menu_list {
		QUIT = 0
	} stat_menu_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, menu::stat_menu_e menu_items)
	 *
	 * \param os: output stream
	 * \param menu_items: menu items in stat window
	 *
	 * Overload << operator to print stat menu items
	 */
	std::ostream& operator<< (std::ostream& os, menu::stat_menu_e menu_items);

	/**
	 * @brief Function: void menu_stat(int entry)
	 *
	 * \param entry: menu entry
	 *
	 * Select menu entry in stat window
	 */
	void menu_stat(int entry);

	/**
	 * @brief Function: void menu_stat_items()
	 *
	 * List menu items in stat window
	 */
	void menu_stat_items();

	class Menu {
		public:
			// Constructor
			Menu(std::string window_title = "", void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): title(window_title), id(create_menu(EntryFunc, ItemsFunc)) {
				std::string pretext ("Menu Constructor");
				menu::Menu::print_info(logging::verb_level_e::LOW, pretext);
			}

			Menu(const Menu& copy): title(copy.title), id(copy.id) {};

			// Destructor
			~Menu();

			int get_id();
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			void destroy_menu();

		protected:
			int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)());

		private:
			std::string title;
			int id;
	};

	/** @} */ // End of MenuGroup group
}

#endif // MENU_H
