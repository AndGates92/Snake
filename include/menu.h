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

#include <map>
#include <string>
#include <iostream>

#include "logging.h"
#include "shared_constants.h"

/** @defgroup MenuGroup Menu Doxygen Group
 *  Menu functions and classes
 *  @{
 */

namespace menu {
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

	/**
	 * @brief Entry function pointer function
	 *
	 */
	typedef void (*EntryFuncPtr)(int);

	/**
	 * @brief Item function pointer function
	 *
	 */
	typedef void (*ItemFuncPtr)(void);

	namespace {
		static std::map <std::string, EntryFuncPtr> EntryFunc = {
			{ shared_constants::game_win_title, menu_game},
			{ shared_constants::stat_win_title, menu_stat}
		};

		static std::map <std::string, ItemFuncPtr> ItemsFunc = {
			{ shared_constants::game_win_title, menu_game_items},
			{ shared_constants::stat_win_title, menu_stat_items}
		};
	}

	/**
	 * @brief Menu class
	 *
	 */
	class Menu {
		public:
			// Constructor
			/**
			 * @brief Function: Menu(std::string window_title = "")
			 *
			 * \param window_title: title of the window
			 *
			 * Menu constructor
			 */
			explicit Menu(std::string window_title = ""): title(window_title), id(create_menu(EntryFunc[window_title], ItemsFunc[window_title])) {
				std::string pretext ("Menu Constructor");
				menu::Menu::print_info(logging::verb_level_e::LOW, pretext);
			}

			/**
			 * @brief Function: Menu(const Menu& copy)
			 *
			 * \param copy: Menu to copy
			 *
			 * Menu copy constructor
			 */
			Menu(const Menu& copy): title(copy.title), id(copy.id) {};

			// Destructor
			/**
			 * @brief Function: ~Menu()
			 *
			 * Menu destructor
			 */
			~Menu();

			/**
			 * @brief Function: void save_data (iofile::File & savefile)
			 *
			 * \param savefile: file to write Menu information to
			 *
			 * Save the Menu information
			 */
			void save_data (iofile::File & savefile);

			/**
			 * @brief Function: int get_id()
			 *
			 * \return menu ID
			 *
			 * Get menu ID
			 */
			int get_id();

			/**
			 * @brief Function: std::string get_title()
			 *
			 * \return title of the menu
			 *
			 * Get title of the menu
			 */
			std::string get_title();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the Menu information
			 *
			 * Print Menu information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void destroy_menu()
			 *
			 * Destroy this menu
			 */
			void destroy_menu();

			/**
			 * @brief Function: bool operator== (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload == operator
			 */
			bool operator== (const menu::Menu & rhs);

			/**
			 * @brief Function: bool operator!= (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload != operator
			 */
			bool operator!= (const menu::Menu & rhs);

		protected:

			/**
			 * @brief Function: int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)())
			 *
			 * \param EntryFunc: function pointer to determine the action to be taken based on the menu item selected
			 * \param ItemsFunc: function pointer to list of item to be shown in the menu
			 *
			 * \return menu ID
			 *
			 * Create menu and return window ID
			 */
			int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)());

		private:
			/**
			 *
			 * @brief Title of the menu
			 *
			 */
			std::string title;

			/**
			 *
			 * @brief Menu ID
			 *
			 */
			int id;

	};

}
/** @} */ // End of MenuGroup group

#endif // MENU_H
