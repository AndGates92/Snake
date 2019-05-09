/**
 * @copyright
 * @file snake_node.cpp
 * @author Andrea Gianarda
 * @date 04th March 2019
 * @brief Snake Node function
 */

#include <iostream>

#include "basic_object.h"
#include "snake_node.h"
#include "snake_utils.h"
#include "logging.h"
#include "graphics_utils.h"

using namespace std;
using namespace snake_node;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
snake_node::SnakeUnit::~SnakeUnit() {
	std::string pretext ("");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void snake_node::SnakeUnit::print_info(logging::verb_level_e verbosity, std::string pretext) {
	basic_object::BasicObject::print_info(verbosity, pretext);
	std::string type = this->get_type();
	LOG_INFO(verbosity, "[", type, " ", pretext, "] Direction ", this->direction, ".");
}

void snake_node::SnakeUnit::save_data (iofile::File & savefile) {
	basic_object::BasicObject::save_data(savefile);
	savefile.write_ofile("Direction: ", this->direction, "\n");
}

// ================================================================
// Get functions
// ================================================================
snake_utils::direction_e snake_node::SnakeUnit::get_direction() {
	return this->direction;
}

// ================================================================
// Set functions
// ================================================================
void snake_node::SnakeUnit::set_direction(snake_utils::direction_e new_direction) {
	this->direction = new_direction;
}

// ================================================================
// Move function
// ================================================================
void snake_node::SnakeUnit::move(const int & speed, const int & win_width, const int & win_height) {

	int y_centre = this->get_y_centre();
	int x_centre = this->get_x_centre();

	switch (this->direction) {
		case snake_utils::direction_e::RIGHT:
			x_centre = (x_centre + speed) % win_width;
			break;
		case snake_utils::direction_e::LEFT:
			if (x_centre < speed) {
				x_centre += win_width;
			}
			x_centre = (x_centre - speed) % win_width;
			break;
		case snake_utils::direction_e::UP:
			y_centre = (y_centre + speed) % win_height;
			break;
		case snake_utils::direction_e::DOWN:
			if (y_centre < speed) {
				y_centre += win_height;
			}
			y_centre = (y_centre - speed) % win_height;
			break;
		default:
			LOG_ERROR("Unknown direction");
			break;
	}

	this->set_y_centre(y_centre);
	this->set_x_centre(x_centre);
}

// ================================================================
// Snake Node
// ================================================================
snake_node::SnakeNode::~SnakeNode() {
	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void snake_node::SnakeNode::print_info(logging::verb_level_e verbosity, std::string pretext) {
	SnakeUnit::print_info(verbosity, pretext);
	std::string name_pretext = this->get_type();
	name_pretext.append(" ");
	name_pretext.append(pretext);
	basic_obj_node::BasicObjNode<SnakeNode>::print_info(verbosity, name_pretext);
}

