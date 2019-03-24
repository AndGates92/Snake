/**
 * @copyright
 * @file obstacle.cpp
 * @author Andrea Gianarda
 * @date 22nd March 2019
 * @brief Obstacle function
 */

#include <iostream>

#include "obstacle.h"
#include "logging.h"
#include "graphics_utils.h"

using namespace std;
using namespace obstacle;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
obstacle::Obstacle::~Obstacle() {
	std::string pretext ("Obstacle");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void obstacle::Obstacle::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Centre coordinares: (X ", this->x_centre, ", Y ", this->y_centre, "), width ", this->width, ", height ", this->height, " colour ", this->colour, ".");
}

// ================================================================
// Get functions
// ================================================================
int obstacle::Obstacle::get_x_centre() {
	return this->x_centre;
}

int obstacle::Obstacle::get_y_centre() {
	return this->y_centre;
}

int obstacle::Obstacle::get_width() {
	return this->width;
}

int obstacle::Obstacle::get_height() {
	return this->height;
}

graphics_utils::palette_e obstacle::Obstacle::get_colour() {
	return this->colour;
}

// ================================================================
// Set functions
// ================================================================
void obstacle::Obstacle::set_x_centre(int new_x_centre) {
	this->x_centre = new_x_centre;
}

void obstacle::Obstacle::set_y_centre(int new_y_centre) {
	this->y_centre = new_y_centre;
}

void obstacle::Obstacle::set_width(int new_width) {
	this->width = new_width;
}

void obstacle::Obstacle::set_height(int new_height) {
	this->height = new_height;
}

void obstacle::Obstacle::set_colour(graphics_utils::palette_e new_colour) {
	this->colour = new_colour;
}

// ================================================================
// Obstacle Node
// ================================================================
obstacle::ObstacleNode::~ObstacleNode() {
	std::string pretext ("Snake Node Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

// ================================================================
// Get functions
// ================================================================

obstacle::ObstacleNode * & obstacle::ObstacleNode::get_next() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Get pointer next: ", this->next);
	return this->next;
}

obstacle::ObstacleNode * & obstacle::ObstacleNode::get_prev() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Get pointer prev: ", this->prev);
	return this->prev;
}

// ================================================================
// Set functions
// ================================================================

void obstacle::ObstacleNode::set_next(obstacle::ObstacleNode * next_ptr) {
	this->next = next_ptr;
}

void obstacle::ObstacleNode::set_prev(obstacle::ObstacleNode * prev_ptr) {
	this->prev = prev_ptr;
}

void obstacle::ObstacleNode::print_info(logging::verb_level_e verbosity, std::string pretext) {
	Obstacle::print_info(verbosity, pretext);
	LOG_INFO(verbosity, "[", pretext, "] Pointer addresses: next ", this->next, " previous " , this->prev, ".");
}
