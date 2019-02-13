#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file window_list.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window header file
*/

#include "menu.h"
#include "window.h"

namespace window_list {
	/** @defgroup WindowListGroup Window List Doxygen Group
	 *  Window List functions and classes
	 *  @{
	 */

	using window::Window;
	using menu::Menu;

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
	/** @} */ // End of WindowGroup group
}

template <typename entry_e>
window_list::WindowObj<entry_e>::~WindowObj() {
	window_list::WindowObj<entry_e>::drawing.~Window();
	window_list::WindowObj<entry_e>::action_list.~Menu();
}
#endif // WINDOW_LIST_H
