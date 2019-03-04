/**
 * @copyright
 * @file snake_unit.cpp
 * @author Andrea Gianarda
 * @date 04th March 2019
 * @brief Snake Unit function
 */

#include <iostream>

#include "snake_unit.h"
#include "log.h"

using namespace std;
using namespace snake_unit;
using namespace log;

// ================================================================
// Destructor
// ================================================================
snake_unit::SnakeUnit::~SnakeUnit() {
	std::string pretext ("Window Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
}

void snake_unit::SnakeUnit::print_info(log::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Centre coordinares: (X ", this->x_centre, ", Y ", this->y_centre, "), direction ", this->direction, " colour ", this->colour, ".");
}

// Overload << operator for direction_e
std::ostream& snake_unit::operator<< (std::ostream& os, snake_unit::direction_e direction) {

	switch (direction) {
		case snake_unit::direction_e::UP:
			os << "UP";
			break;
		case snake_unit::direction_e::DOWN:
			os << "DOWN";
			break;
		case snake_unit::direction_e::LEFT:
			os << "LEFT";
			break;
		case snake_unit::direction_e::RIGHT:
			os << "RIGHT";
			break;
		default:
			os << "Unknown direction";
			break;
	}

	return os;
}
