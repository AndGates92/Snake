/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief Window List function
 */

#include <iostream>

#include "window_list.h"
#include "window_node.h"
#include "window_obj.h"
#include "logging.h"

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;
using namespace logging;
using namespace window_list;
using namespace window_obj;
using namespace window_node;

window_list::WindowList::~WindowList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	this->~BasicObjList();

	LOG_INFO(logging::verb_level_e::HIGH, "Window list destroyed");

}

void window_list::WindowList::add_node(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos , void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)()) {

	window_node::WindowNode * head(this->get_head());

	LOG_INFO(logging::verb_level_e::LOW, "[Add node] Create node at ", window_x_pos, ", ", window_y_pos, ". Dimensions: width ", window_width, " height ", window_height, ". Title: ", window_title);
	window_node::WindowNode * new_window = new window_node::WindowNode(window_title, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc);
	if (new_window == nullptr) {
		LOG_ERROR("Can't allocate memory for window node");
	}

	new_window->set_prev(nullptr);

	if(head != nullptr) {
		head->set_prev(new_window);
	}

	new_window->set_next(head);
	this->set_head(new_window);

}

void window_list::WindowList::delete_by_win_id(int &win_id) {

	window_node::WindowNode * head(this->get_head());
	window_node::WindowNode * window_node (head);

	while (window_node != nullptr) {

		// temporary node
		window_obj::WindowObj node = window_node->get_obj();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

		// Current ID matches searched ID
		if (curr_win_id == win_id) {
			// Delete node from linked list
			this->delete_node(window_node);
			return;
		}

		window_node = window_node->get_next();

	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
}

window_node::WindowNode * window_list::WindowList::search_by_win_id(int &win_id) {

	window_node::WindowNode * head(this->get_head());
	window_node::WindowNode * window_node (head);

	while (window_node != nullptr) {

		window_obj::WindowObj node = window_node->get_obj();
		int curr_win_id = 0;
		curr_win_id = node.get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

		// Current ID matches searched ID
		if (curr_win_id == win_id) {
			window_node::WindowNode * window_found = window_node;
			return window_found;
		}

		window_node = window_node->get_next();

	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
	window_node::WindowNode * node_err = new window_node::WindowNode("Error");
	if (node_err == nullptr) {
		LOG_ERROR("Can't allocate memory for error node");
	}
	return node_err;
}

void window_list::WindowList::delete_node(window_node::WindowNode * & node) {
	this->remove_node(node);
	node->destroy_node();
}

