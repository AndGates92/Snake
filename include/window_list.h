#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file window_list.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window List header file
*/

#include "window_obj.h"

namespace window_list {
	/** @defgroup WindowListGroup Window List Doxygen Group
	 *  Window List functions and classes
	 *  @{
	 */

	template <typename entry_e>
	class WindowNode {
		public:
			// Constructor
			WindowNode(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (&EntryFunc)(entry_e) = nullptr, void (*ItemsFunc)() = nullptr);

			// Destructor
			~WindowNode();

		protected:

		private:
			WindowList * prev;
			window_obj::WindowObj<entry_e> node;
			WindowNode *next;
	};
	/** @} */ // End of WindowListGroup group
}


#endif // WINDOW_LIST_H
