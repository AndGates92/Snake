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

	std::string pretext ("Window List Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);

	window_node::WindowNode * node_ptr = nullptr;
	while (this->head != nullptr) {
		node_ptr = this->head;
		this->head = this->head->get_next();
		node_ptr->destroy_node();
		node_ptr->~WindowNode();
		delete [] node_ptr;
	}
	LOG_INFO(log::verb_level_e::HIGH, "Window list destroyed");

}


void window_list::WindowList::add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)()) {

	LOG_INFO(log::verb_level_e::LOW, "[Add node] Create node at ", window_x_pos, ", ", window_y_pos, ". Dimensions: width ", window_width, " height ", window_height, ". Title: ", window_title);
	window_node::WindowNode * new_window = new window_node::WindowNode(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc);

	new_window->set_prev(nullptr);

	if(this->head != nullptr) {
		this->head->set_prev(new_window);
	}

	new_window->set_next(this->head);
	this->head = new_window;

}

void window_list::WindowList::delete_by_win_id(int &win_id) {

	window_node::WindowNode * window_nodes = this->head;

	while (window_nodes != nullptr) {

		// temporary node
		window_obj::WindowObj node = window_nodes->get_node();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(log::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

		// Current ID matches searched ID
		if (curr_win_id == win_id) {
			// Delete node from linked list
			remove_node(window_nodes);
			return;
		}

		window_nodes = window_nodes->get_next();

	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
}

void window_list::WindowList::remove_node(window_node::WindowNode * & node) {
	window_node::WindowNode * node_saved = node;

	if (node == this->head) {
		// Move head pointer as window list to delete is the head
		if (node->get_next() == nullptr) {
			this->head = nullptr;
		} else {
			this->head = this->head->get_next();
			this->head->get_prev() = nullptr;
		}
	} else {
		node->get_prev()->get_next() = node->get_next();
		if (node->get_next() != nullptr) {
			node->get_next()->get_prev() = node->get_prev();
		}
	}

	node_saved->destroy_node();
	node_saved->~WindowNode();
}

window_obj::WindowObj window_list::WindowList::search_by_win_id(int &win_id) {

	window_node::WindowNode * window_nodes = this->head;

	while (window_nodes != nullptr) {

		window_obj::WindowObj node = window_nodes->get_node();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(log::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

		// Current ID matches searched ID
		if (curr_win_id == win_id) {
			window_obj::WindowObj window_found = node;
			return window_found;
		}

		window_nodes = window_nodes->get_next();

	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
	window_obj::WindowObj obj_err("Error");
	return obj_err;
}

void window_list::WindowList::print_info(log::verb_level_e verbosity, std::string pretext) {
	window_node::WindowNode * window_list = nullptr;
	// Initially point to the head
	window_list = this->head;

	while (window_list != nullptr) {
		window_obj::WindowObj node;
		node = this->head->get_node();
		node.print_info(verbosity, pretext);
		window_list = window_list->get_next();
	}
}
