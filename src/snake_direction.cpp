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
	LOG_INFO(logging::verb_level_e::DEBUG, "Snake Direction Destructor");
}

void snake_direction::SnakeDirection::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] ", *this, ".");
}

// ================================================================
// Get functions
// ================================================================
snake_utils::direction_e snake_direction::SnakeDirection::get_direction() const {
	return this->direction;
}

// ================================================================
// Set functions
// ================================================================
void snake_direction::SnakeDirection::set_direction(snake_utils::direction_e new_direction) {
	this->direction = new_direction;
}

std::ostream& snake_direction::operator<< (std::ostream& os, const snake_direction::SnakeDirection & dir) {
	os << "Direction " << dir.get_direction();
	return os;
}
