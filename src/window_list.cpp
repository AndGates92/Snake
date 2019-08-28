/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief Window List function
 */

#include <iostream>
#include <algorithm>

#include "window_list.h"
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
using namespace window_obj;

window_list::WindowList::~WindowList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	this->~BasicObjList();

	LOG_INFO(logging::verb_level_e::HIGH, "Window list destroyed");

}

int window_list::WindowList::add_element(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour) {

	std::vector<window_obj::WindowObj> win_vector(this->get_head());

	LOG_INFO(logging::verb_level_e::LOW, "[Add node] Create node at ", window_x_pos, ", ", window_y_pos, ". Dimensions: width ", window_width, " height ", window_height, ". Title: ", window_title, " Background colour: ", background_colour);
	window_obj::WindowObj new_window = window_obj::WindowObj(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour);

	win_vector.insert(win_vector.begin(), new_window);

	int win_id = new_window.get_win_id();
	return win_id;

}

void window_list::WindowList::delete_by_win_id(int &win_id) {

	std::vector<window_obj::WindowObj> win_vector(this->get_head());

	// Delete all nodes with ID equal to win_id
	std::vector<window_obj::WindowObj>::iterator element_it = std::find_if(win_vector.begin(), win_vector.end(), is_matching::IsMatching<int, window_obj::WindowObj>(win_id));
	if (element_it != win_vector.end()) {
		win_vector.erase(element_it);
	} else {
		LOG_ERROR("Window with ID ", win_id, " has not been found");
	}

	LOG_ERROR("Couldn't find window matching window ID ", win_id);
}

window_obj::WindowObj window_list::WindowList::search_by_win_id(int &win_id) {

	std::vector<window_obj::WindowObj> win_vector(this->get_head());

	// Delete all nodes with ID equal to win_id
	std::vector<window_obj::WindowObj>::iterator element_it = std::find_if(win_vector.begin(), win_vector.end(), is_matching::IsMatching<int, window_obj::WindowObj>(win_id));
	if (element_it != win_vector.end()) {
		return *element_it;
	} else {
		LOG_ERROR("Couldn't find window matching window ID ", win_id);
		window_obj::WindowObj node_err = window_obj::WindowObj("Error");
		return node_err;
	}
}

void window_list::WindowList::delete_element(window_obj::WindowObj & node) {
	this->delete_element(node);
	node.destroy_obj();
}

