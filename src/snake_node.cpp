/**
 * @copyright
 * @file snake_node.cpp
 * @author Andrea Gianarda
 * @date 04th March 2019
 * @brief Snake Unit function
 */

#include <iostream>

#include "snake_node.h"
#include "log.h"
#include "graphics_utils.h"

using namespace std;
using namespace snake_node;
using namespace log;

// ================================================================
// Destructor
// ================================================================
snake_node::SnakeUnit::~SnakeUnit() {
	std::string pretext ("Window Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
}

void snake_node::SnakeUnit::print_info(log::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Centre coordinares: (X ", this->x_centre, ", Y ", this->y_centre, "), direction ", this->direction, " colour ", this->colour, ".");
}

// ================================================================
// Get functions
// ================================================================
int snake_node::SnakeUnit::get_x_centre() {
	return x_centre;
}

int snake_node::SnakeUnit::get_y_centre() {
	return y_centre;
}

snake_node::direction_e snake_node::SnakeUnit::get_direction() {
	return direction;
}

graphics_utils::palette_e snake_node::SnakeUnit::get_colour() {
	return colour;
}

// ================================================================
// Set functions
// ================================================================
void snake_node::SnakeUnit::set_x_centre(int new_x_centre) {
	this->x_centre = new_x_centre;
}

void snake_node::SnakeUnit::set_y_centre(int new_y_centre) {
	this->y_centre = new_y_centre;
}

void snake_node::SnakeUnit::set_direction(snake_node::direction_e new_direction) {
	this->direction = new_direction;
}

void snake_node::SnakeUnit::set_colour(graphics_utils::palette_e new_colour) {
	this->colour = new_colour;
}

// ================================================================
// Overload << operator for direction_e
// ================================================================
std::ostream& snake_node::operator<< (std::ostream& os, snake_node::direction_e direction) {

	switch (direction) {
		case snake_node::direction_e::UP:
			os << "UP";
			break;
		case snake_node::direction_e::DOWN:
			os << "DOWN";
			break;
		case snake_node::direction_e::LEFT:
			os << "LEFT";
			break;
		case snake_node::direction_e::RIGHT:
			os << "RIGHT";
			break;
		default:
			os << "Unknown direction";
			break;
	}

	return os;
}

// ================================================================
// Snake Node
// ================================================================
snake_node::SnakeNode::~SnakeNode() {
	std::string pretext ("Snake Node Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
}

// ================================================================
// Get functions
// ================================================================

snake_node::SnakeNode * & snake_node::SnakeNode::get_next() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer next: ", this->next);
	return this->next;
}

snake_node::SnakeNode * & snake_node::SnakeNode::get_prev() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer prev: ", this->prev);
	return this->prev;
}

// ================================================================
// Set functions
// ================================================================

void snake_node::SnakeNode::set_next(snake_node::SnakeNode * next_ptr) {
	this->next = next_ptr;
}

void snake_node::SnakeNode::set_prev(snake_node::SnakeNode * prev_ptr) {
	this->prev = prev_ptr;
}

void snake_node::SnakeNode::print_info(log::verb_level_e verbosity, std::string pretext) {
	SnakeUnit::print_info(verbosity, pretext);
	if (this->prev != nullptr) {
		this->prev->print_info(verbosity, pretext);
	}

	if (this->next != nullptr) {
		this->next->print_info(verbosity, pretext);
	}
}
