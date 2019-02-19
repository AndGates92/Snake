#ifndef WINDOW_OBJ_H
#define WINDOW_OBJ_H
/**
 * @copyright
 * @file window_obj.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window Object header file
*/

#include "log.h"
#include "menu.h"
#include "window.h"

namespace window_obj {
	/** @defgroup WindowObjectGroup Window Object Doxygen Group
	 *  Window Object functions and classes
	 *  @{
	 */

	class WindowObj {
		public:
			// Constructor
			WindowObj(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): drawing(window_title, window_width, window_height, window_x_pos, window_y_pos), action_list(EntryFunc, ItemsFunc) {};

			WindowObj(const WindowObj& copy): drawing(copy.drawing), action_list(copy.action_list) {};

			// Destructor
			~WindowObj();

			int get_win_id();
			int get_menu_id();
			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			window::Window drawing;
			menu::Menu action_list;
	};
	/** @} */ // End of WindowObjectGroup group
}

#endif // WINDOW_OBJ_H
