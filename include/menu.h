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

	void menu_snake(int entry);

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

		protected:
			int create_menu(void (*EntryFunc)(int), void (*ItemsFunc)());
			void destroy_menu();

		private:
			int id;
	};

	/** @} */ // End of MenuGroup group
}

#endif // MENU_H
