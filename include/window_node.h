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
			WindowNode(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (&EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr): node(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc), prev(nullptr), next(nullptr) {};

			WindowNode(const WindowNode<entry_e>& copy) : node(copy.node), prev(copy.prev), next(copy.next) { LOG_INFO(log::verb_level_e::LOW, "Window node copy contructor") };

			// Destructor
			~WindowNode();

			// Get functions
			WindowNode * get_next();
			WindowNode * get_prev();
			window_obj::WindowObj<entry_e> get_node();

			// Set functions
			void set_next(WindowNode * next_ptr);
			void set_prev(WindowNode * prev_ptr);
			void set_node(window_obj::WindowObj<entry_e> node);

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

template <typename entry_e>
window_node::WindowNode<entry_e> * window_node::WindowNode<entry_e>::get_prev() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer next", this.next);
	return this.next;
}

template <typename entry_e>
window_obj::WindowObj<entry_e> window_node::WindowNode<entry_e>::get_node() {
	this.node.print_info(log::verb_level_e::DEBUG, "Get current node");
	return this.node;
}

template <typename entry_e>
window_node::WindowNode<entry_e> * window_node::WindowNode<entry_e>::get_next() {

	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer prev", this.prev);
	return this.prev;

}

template <typename entry_e>
void window_node::WindowNode<entry_e>::set_next(window_node::WindowNode<entry_e> * next_ptr) {
	this->next = next_ptr;
}

template <typename entry_e>
void window_node::WindowNode<entry_e>::set_prev(window_node::WindowNode<entry_e> * prev_ptr) {
	this->prev = prev_ptr;
}

template <typename entry_e>
void window_node::WindowNode<entry_e>::set_node(window_obj::WindowObj<entry_e> node) {
	this->node = node;
}

#endif // WINDOW_NODE_H
