/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief File function
 */

#include <iostream>

#include "window_list.h"
#include "window_node.h"
#include "window_obj.h"
#include "log.h"

using namespace std;
using namespace log;
using namespace window_list;
using namespace window_obj;
using namespace window_node;

window_list::WindowList::~WindowList() {

	window_node::WindowNode * node_ptr = nullptr;
	while (head != nullptr) {
		node_ptr = head->get_next();
		head->~WindowNode();
		head = node_ptr;
	}
	LOG_INFO(log::verb_level_e::HIGH, "Window list destroyed");

}


void window_list::WindowList::add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (*EntryFunc)(int), void (*ItemsFunc)()) {

	window_node::WindowNode * new_window = (window_node::WindowNode *) ::operator new (sizeof(window_node::WindowNode *));
	window_obj::WindowObj node(window_title, window_width, window_height, window_x_pos, window_y_pos , EntryFunc, ItemsFunc);

	new_window->set_node(node);
	new_window->set_prev(nullptr);

	if(head != nullptr) {
		head->set_prev(new_window);
	}

	new_window->set_next(head);
	head = new_window;

}

window_obj::WindowObj window_list::WindowList::search_by_win_id(int win_id) {

	window_node::WindowNode * window_list = nullptr;
	// Initially point to the head
	window_list = head;


	while (window_list != nullptr) {

		window_obj::WindowObj node;
		node = head->get_node();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(log::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current %0d searched %0d",  curr_win_id, win_id);

		if (curr_win_id == win_id) {
			window_obj::WindowObj window_found = node;
			return window_found;
		}

		window_list = window_list->get_next();

	}

	log::log_error("Couldn't find window matching window ID ", win_id);
	window_obj::WindowObj obj_err("Error");
	return obj_err;
}
