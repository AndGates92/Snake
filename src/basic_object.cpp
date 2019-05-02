/**
 * @copyright
 * @file basic_object.cpp
 * @author Andrea Gianarda
 * @date 25th March 2019
 * @brief Basic Object function
 */

#include <iostream>

#include "basic_object.h"
#include "colours.h"
#include "logging.h"

using namespace std;
using namespace basic_object;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
basic_object::BasicObject::~BasicObject() {
	LOG_INFO(logging::verb_level_e::LOW, "Basic Object Destructor")
//	std::string pretext ("");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}

void basic_object::BasicObject::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", this->name, " ",  pretext, "] Centre coordinares: (X ", this->x_centre, ", Y ", this->y_centre, "), width ", this->width, ", height ", this->height, " colour ", this->colour, ".");
}

// ================================================================
// Get functions
// ================================================================
int basic_object::BasicObject::get_x_centre() {
	return this->x_centre;
}

int basic_object::BasicObject::get_y_centre() {
	return this->y_centre;
}

int basic_object::BasicObject::get_width() {
	return this->width;
}

int basic_object::BasicObject::get_height() {
	return this->height;
}

colours::palette_e basic_object::BasicObject::get_colour() {
	return this->colour;
}

std::string basic_object::BasicObject::get_name() {
	return this->name;
}

// ================================================================
// Set functions
// ================================================================
void basic_object::BasicObject::set_x_centre(int new_x_centre) {
	this->x_centre = new_x_centre;
}

void basic_object::BasicObject::set_y_centre(int new_y_centre) {
	this->y_centre = new_y_centre;
}

void basic_object::BasicObject::set_width(int new_width) {
	this->width = new_width;
}

void basic_object::BasicObject::set_height(int new_height) {
	this->height = new_height;
}

void basic_object::BasicObject::set_colour(colours::palette_e new_colour) {
	this->colour = new_colour;
}

void basic_object::BasicObject::set_name (std::string name_obj) {
	this->name = name_obj;
}
