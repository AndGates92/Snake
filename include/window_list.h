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
#include "basic_obj_list.h"

namespace window_list {
	/** @defgroup WindowListGroup Window List Doxygen Group
	 *  Window List functions and classes
	 *  @{
	 */

	class WindowList : public basic_obj_list::BasicObjList<window_node::WindowNode> {
		public:
			// Constructor
			WindowList(std::string name_win = "Window"): basic_obj_list::BasicObjList<window_node::WindowNode>(name_win) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			WindowList(const WindowList& copy): basic_obj_list::BasicObjList<window_node::WindowNode>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~WindowList();

			int add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)(), colours::palette_e background_colour);

			window_node::WindowNode * search_by_win_id(int &win_id);

			void delete_by_win_id(int &win_id);

		protected:
			void delete_node(window_node::WindowNode * & node);

		private:
	};
	/** @} */ // End of WindowListGroup group
}

#endif // WINDOW_LIST_H
