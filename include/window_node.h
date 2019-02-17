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

	template <typename entry_e>
	class WindowNode {
		public:
			// Constructor
			WindowNode(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (&EntryFunc)(entry_e) = nullptr, void (*ItemsFunc)() = nullptr): node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc) {};

			// Destructor
			~WindowNode();

		protected:

		private:
			WindowNode * prev;
			window_obj::WindowObj<entry_e> node;
			WindowNode * next;
	};
	/** @} */ // End of WindowNodeGroup group
}

template <typename entry_e>
window_node::WindowNode<entry_e>::~WindowNode() {

	LOG_INFO(log::verb_level_e::HIGH, "Window node destroyed");
	delete[] node;

}

#endif // WINDOW_NODE_H
