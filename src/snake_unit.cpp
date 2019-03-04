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
	LOG_INFO(verbosity, "[", pretext, "] Centre coordinares: (X ", this->x_centre, ", Y ", this->y_centre, "), direction ", this->direction, ".");
}

std::ostream& snake_unit::operator<< (std::ostream& os, snake_unit::direction_e direction) {

	switch (direction) {
		case snake_unit::direction_e::UP:
			return os << "UP";
			break;
		case snake_unit::direction_e::DOWN:
			return os << "DOWN";
			break;
		case snake_unit::direction_e::LEFT:
			return os << "LEFT";
			break;
		case snake_unit::direction_e::RIGHT:
			return os << "LEFT";
			break;
		default:
			return os << "UNKNOWN";
			break;
	}

	return os << static_cast<std::uint32_t>(direction);
}
