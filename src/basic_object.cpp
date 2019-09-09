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
#include "file.h"

// ================================================================
// Destructor
// ================================================================
basic_object::BasicObject::~BasicObject() {
	LOG_INFO(logging::verb_level_e::LOW, "Basic Object Destructor")
	std::string pretext ("");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void basic_object::BasicObject::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", this->type, " ",  pretext, "] ", this, ".");
}

// ================================================================
// Get functions
// ================================================================
int basic_object::BasicObject::get_x_centre() const {
	return this->x_centre;
}

int basic_object::BasicObject::get_y_centre() const {
	return this->y_centre;
}

int basic_object::BasicObject::get_width() const {
	return this->width;
}

int basic_object::BasicObject::get_height() const {
	return this->height;
}

colours::palette_e basic_object::BasicObject::get_colour() const {
	return this->colour;
}

std::string basic_object::BasicObject::get_type() const {
	return this->type;
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

void basic_object::BasicObject::set_type (std::string type_obj) {
	this->type = type_obj;
}

void basic_object::BasicObject::save_data (iofile::File & savefile) {
	savefile.write_ofile("Type: ", this->type, "\n");
	savefile.write_ofile("X: ", this->x_centre, "\n");
	savefile.write_ofile("Y: ", this->y_centre, "\n");
	savefile.write_ofile("Width: ", this->width, "\n");
	savefile.write_ofile("Height: ", this->height, "\n");
	savefile.write_ofile("Colour: ", this->colour, "\n");
}

bool basic_object::BasicObject::operator== (const basic_object::BasicObject & rhs) {
	bool same_type = (this->type.compare(rhs.type) == 0);
	bool same_x_centre = (this->x_centre == rhs.x_centre);
	bool same_y_centre = (this->y_centre == rhs.y_centre);
	bool same_width = (this->width == rhs.width);
	bool same_height = (this->height == rhs.height);
	bool same_colour = (this->colour == rhs.colour);
	return (same_type && same_x_centre && same_y_centre && same_width && same_height && same_colour);
}

bool basic_object::BasicObject::operator!= (const basic_object::BasicObject & rhs) {
	bool different_type = (this->type.compare(rhs.type) != 0);
	bool different_x_centre = (this->x_centre != rhs.x_centre);
	bool different_y_centre = (this->y_centre != rhs.y_centre);
	bool different_width = (this->width != rhs.width);
	bool different_height = (this->height != rhs.height);
	bool different_colour = (this->colour != rhs.colour);
	return (different_type && different_x_centre && different_y_centre && different_width && different_height && different_colour);
}

std::ostream& operator<< (std::ostream& os, const basic_object::BasicObject & object) {
	os << " Type " << object.get_type() << " Centre coordinares: (X " << object.get_x_centre() << ", Y " << object.get_y_centre() << "), width " << object.get_width() << ", height " << object.get_height() << " colour " << object.get_colour();

	return os;
}
