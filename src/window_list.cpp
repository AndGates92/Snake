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
#include "is_matching.h"

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;
using namespace logging;
using namespace is_matching;
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

	this->head.insert(new_window);

	int win_id = new_window->get_win_id();
	return win_id;

}

bool window_list::WindowList::does_win_id_match(window_node::WindowObj obj) {
	// temporary node
	int curr_win_id = node->get_win_id();

	LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

	// Current ID matches searched ID
	return (curr_win_id == win_id);
}

void window_list::WindowList::delete_by_win_id(int &win_id) {

	std::vector<window_node::WindowObj> head(this->get_head());

	// Delete all nodes with ID equal to win_id
	std::vector<class_element>::iterator element_it = std::find_if(this->head.begin(), this->head.end(), is_matching::IsMatching(win_id));
	if (element_it != this->head.end()) {
		this->head.erase(element_it);
	} else {
		LOG_ERROR("Window with ID ", win_id, " has not been found");
	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
}

window_node::WindowObj * window_list::WindowList::search_by_win_id(int &win_id) {

	window_node::WindowObj * head(this->get_head());
	window_node::WindowObj * window_node (head);

	// Delete all nodes with ID equal to win_id
	std::vector<class_element>::iterator element_it = std::find_if(this->head.begin(), this->head.end(), is_matching::IsMatching(win_id));
	if (element_it != this->head.end()) {
		return element_it;
	} else {
		LOG_ERROR("Couldn't find window matching window ID ", win_id);
		window_node::WindowObj * node_err = new window_node::WindowObj("Error");
		if (node_err == nullptr) {
			LOG_ERROR("Can't allocate memory for error node");
		}
		return node_err;
	}
}

void window_list::WindowList::delete_node(window_node::WindowObj * & node) {
	this->remove_node(node);
	node->destroy_node();
}

