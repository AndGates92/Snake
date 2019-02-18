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

	template <typename entry_e>
	class WindowList {
		public:
			// Constructor
			WindowList();

			WindowList(const WindowList<entry_e>& copy): head(copy,head) { LOG_INFO(log::verb_level_e::LOW, "Window list copy contructor") };

			// Destructor
			~WindowList();

			void add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (&EntryFunc)(entry_e), void (*ItemsFunc)());
			void remove_node(window_node::WindowNode<entry_e> * node);

			window_obj::WindowObj<entry_e> search_by_win_id(int win_id);

		protected:

		private:
			window_node::WindowNode<entry_e> * head;
	};
	/** @} */ // End of WindowListGroup group
}

template <typename entry_e>
window_list::WindowList<entry_e>::~WindowList() {

	window_node::WindowNode<entry_e> * node_ptr = nullptr;
	while (head != nullptr) {
		node_ptr = head->next;
		head.~WindowNode();
		head = node_ptr;
	}
	LOG_INFO(log::verb_level_e::HIGH, "Window list destroyed");

}

template <typename entry_e>
window_list::WindowList<entry_e>::WindowList() {
	LOG_INFO(log::verb_level_e::HIGH, "Window list destroyed");
	head = (window_node::WindowNode<entry_e> *) ::operator new (sizeof(window_node::WindowNode<entry_e> *)) ;
}

template <typename entry_e>
void window_list::WindowList<entry_e>::add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (&EntryFunc)(entry_e), void (*ItemsFunc)()) {

}

template <typename entry_e>
window_obj::WindowObj<entry_e> window_list::WindowList<entry_e>::search_by_win_id(int win_id) {

	window_list::WindowList<entry_e> * window_list = NULL;
	// Initially point to the head
	window_list = head;

	window_obj::WindowObj<entry_e> window_found = NULL;

	while (window_list != NULL) {

		window_obj::WindowObj<entry_e> node;
		node = head->get_node();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(log::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current %0d searched %0d",  curr_win_id, win_id);

		if (curr_win_id == win_id) {
			window_found = node;
			return window_found;
		}

		window_list = window_list->get_next();

	}

	log::log_error("Couldn't find window matching window ID ", win_id);
	return NULL;
}
#endif // WINDOW_LIST_H
