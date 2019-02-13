#ifndef WINDOW_OBJ_H
#define WINDOW_OBJ_H
/**
 * @copyright
 * @file window_obj.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window Object header file
*/

#include "menu.h"
#include "window.h"

namespace window_obj {
	/** @defgroup WindowObjectGroup Window Object Doxygen Group
	 *  Window Object functions and classes
	 *  @{
	 */

	template <typename entry_e>
	class WindowObj {
		public:
			// Constructor
			WindowObj(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (&EntryFunc)(entry_e) = nullptr, void (*ItemsFunc)() = nullptr): drawing(window_title, window_width, window_height, window_x_pos, window_y_pos), action_list(EntryFunc, ItemsFunc) {};

			// Destructor
			~WindowObj();

		protected:

		private:
			window::Window drawing;
			menu::Menu<entry_e> action_list;
	};
	/** @} */ // End of WindowObjectGroup group
}

template <typename entry_e>
window_obj::WindowObj<entry_e>::~WindowObj() {
	window_obj::WindowObj<entry_e>::drawing.~Window();
	window_obj::WindowObj<entry_e>::action_list.~Menu();
}
#endif // WINDOW_OBJ_H
