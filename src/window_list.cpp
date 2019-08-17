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
#include "colours.h"

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

int window_list::WindowList::add_node(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour) {

	window_node::WindowObj * head(this->get_head());

	LOG_INFO(logging::verb_level_e::LOW, "[Add node] Create node at ", window_x_pos, ", ", window_y_pos, ". Dimensions: width ", window_width, " height ", window_height, ". Title: ", window_title, " Background colour: ", background_colour);
	window_node::WindowObj * new_window = new window_node::WindowObj(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour);
	if (new_window == nullptr) {
		LOG_ERROR("Can't allocate memory for window node");
	}

	new_window->set_prev(nullptr);

	if(head != nullptr) {
		head->set_prev(new_window);
	}

	new_window->set_next(head);
	this->set_head(new_window);

	int win_id = new_window->get_win_id();
	return win_id;

}

void window_list::WindowList::delete_by_win_id(int &win_id) {

	window_node::WindowObj * head(this->get_head());
	window_node::WindowObj * window_node (head);

	while (window_node != nullptr) {

		// temporary node
		int curr_win_id = window_node->get_win_id();

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

window_node::WindowObj * window_list::WindowList::search_by_win_id(int &win_id) {

	window_node::WindowObj * head(this->get_head());
	window_node::WindowObj * window_node (head);

	while (window_node != nullptr) {

		int curr_win_id = window_node->get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

		// Current ID matches searched ID
		if (curr_win_id == win_id) {
			window_node::WindowObj * window_found = window_node;
			return window_found;
		}

		window_node = window_node->get_next();

	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
	window_node::WindowObj * node_err = new window_node::WindowObj("Error");
	if (node_err == nullptr) {
		LOG_ERROR("Can't allocate memory for error node");
	}
	return node_err;
}

void window_list::WindowList::delete_node(window_node::WindowObj * & node) {
	this->remove_node(node);
	node->destroy_node();
}

