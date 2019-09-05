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
