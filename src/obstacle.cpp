/**
 * @copyright
 * @file obstacle.cpp
 * @author Andrea Gianarda
 * @date 04th March 2019
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
