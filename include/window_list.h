#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file window_list.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window List header file
*/

#include "window_node.h"

namespace window_list {
	/** @defgroup WindowListGroup Window List Doxygen Group
	 *  Window List functions and classes
	 *  @{
	 */

	class WindowList {
		public:
			// Constructor
			WindowList(): head(nullptr) {};

			WindowList(const WindowList& copy): head(copy.head) { LOG_INFO(log::verb_level_e::LOW, "Window list copy contructor") };

			// Destructor
			~WindowList();

			void add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (*EntryFunc)(int), void (*ItemsFunc)());
			void remove_node(window_node::WindowNode * node);

			window_obj::WindowObj search_by_win_id(int win_id);

			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			window_node::WindowNode * head;
	};
	/** @} */ // End of WindowListGroup group
}

#endif // WINDOW_LIST_H
