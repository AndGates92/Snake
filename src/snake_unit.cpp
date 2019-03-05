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

// ================================================================
// Get functions
// ================================================================
int snake_unit::SnakeUnit::get_x_centre() {
	return x_centre;
}

int snake_unit::SnakeUnit::get_y_centre() {
	return y_centre;
}

snake_unit::direction_e snake_unit::SnakeUnit::get_direction() {
	return direction;
}

graphics_utils::palette_e snake_unit::SnakeUnit::get_colour() {
	return colour;
}

// ================================================================
// Set functions
// ================================================================
void snake_unit::SnakeUnit::set_x_centre(int new_x_centre) {
	this->x_centre = new_x_centre;
}

void snake_unit::SnakeUnit::set_y_centre(int new_y_centre) {
	this->y_centre = new_y_centre;
}

void snake_unit::SnakeUnit::set_direction(snake_unit::direction_e new_direction) {
	this->direction = new_direction;
}

void snake_unit::SnakeUnit::set_colour(graphics_utils::palette_e new_colour) {
	this->colour = new_colour;
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
