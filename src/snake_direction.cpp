/**
 * @copyright
 * @file snake_direction.cpp
 * @author Andrea Gianarda
 * @date 30th June 2019
 * @brief Snake Direction Class function
 */

#include <iostream>

#include "snake_direction.h"
#include "snake_utils.h"
#include "logging.h"

using namespace std;
using namespace snake_direction;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
snake_direction::SnakeDirection::~SnakeDirection() {
	std::string pretext ("");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void snake_direction::SnakeDirection::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Direction ", this->direction, ".");
}

// ================================================================
// Get functions
// ================================================================
snake_utils::direction_e snake_direction::SnakeDirection::get_direction() {
	return this->direction;
}

// ================================================================
// Set functions
// ================================================================
void snake_direction::SnakeDirection::set_direction(snake_utils::direction_e new_direction) {
	this->direction = new_direction;
}

// ================================================================
// Snake Node
// ================================================================
snake_direction::SnakeDirectionNode::~SnakeDirectionNode() {
	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void snake_direction::SnakeDirectionNode::print_info(logging::verb_level_e verbosity, std::string pretext) {
	SnakeDirection::print_info(verbosity, pretext);
	std::string name_pretext(pretext);
	basic_obj_node::BasicObjNode<SnakeDirectionNode>::print_info(verbosity, name_pretext);
}

