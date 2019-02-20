#ifndef WINDOW_NODE_H
#define WINDOW_NODE_H
/**
 * @copyright
 * @file window_node.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window Node header file
*/

#include "window_obj.h"

namespace window_node {
	/** @defgroup WindowNodeGroup Window Node Doxygen Group
	 *  Window Node functions and classes
	 *  @{
	 */

	class WindowNode {
		public:
			// Constructor
			WindowNode(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc), prev(nullptr), next(nullptr) {
				std::string pretext ("Window Node Constructor");
				window_node::WindowNode::print_info(log::verb_level_e::LOW, pretext);
			};

			WindowNode(const WindowNode& copy) : node(copy.node), prev(copy.prev), next(copy.next) { LOG_INFO(log::verb_level_e::LOW, "Window node copy contructor") };

			// Destructor
			~WindowNode();

			// Get functions
			WindowNode * get_next();
			WindowNode * get_prev();
			window_obj::WindowObj get_node();

			// Set functions
			void set_next(WindowNode * next_ptr);
			void set_prev(WindowNode * prev_ptr);
			void set_node(window_obj::WindowObj node);

			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			window_obj::WindowObj node;
			WindowNode * prev;
			WindowNode * next;
	};
	/** @} */ // End of WindowNodeGroup group
}

#endif // WINDOW_NODE_H
