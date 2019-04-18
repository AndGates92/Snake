/**
 * @copyright
 * @file settings.cpp
 * @author Andrea Gianarda
 * @date 17th April 2019
 * @brief Settings function
 */

#include <iostream>

#include "settings.h"
#include "logging.h"
#include "snake_node.h"
#include "graphics_utils.h"

using namespace std;
using namespace logging;
using namespace settings;

// ================================================================
// Get functions
// ================================================================
bool settings::Settings::get_hard_wall_flag() {
	return this->hard_wall;
}

std::string settings::Settings::get_save_filename() {
	return this->save_filename;
}

int settings::Settings::get_speed() {
	return this->speed;
}

int settings::Settings::get_speed_incr() {
	return this->speed_incr;
}

int settings::Settings::get_node_height() {
	return this->node_height;
}

int settings::Settings::get_node_width() {
	return this->node_width;
}

int settings::Settings::get_snake_units() {
	return this->snake_units;
}

int settings::Settings::get_obs_no() {
	return this->obs_no;
}

int settings::Settings::get_head_centre_x() {
	return this->head_centre_x;
}

int settings::Settings::get_head_centre_y() {
	return this->head_centre_y;
}

snake_node::direction_e settings::Settings::get_head_dir() {
	return this->head_dir;
}

graphics_utils::palette_e settings::Settings::get_snake_color() {
	return this->snake_color;
}

graphics_utils::palette_e settings::Settings::get_obs_color() {
	return this->obs_color;
}

// ================================================================
// Set functions
// ================================================================
void settings::Settings::set_hard_wall_flag(bool value) {
	this->hard_wall = value;
}

void settings::Settings::set_save_filename(std::string name) {
	this->save_filename = name;
}

void settings::Settings::set_speed(int value) {
	this->speed = value;
}

void settings::Settings::set_speed_incr(int value) {
	this->speed_incr = value;
}

void settings::Settings::set_node_height(int value) {
	this->node_height = value;
}

void settings::Settings::set_node_width(int value) {
	this->node_width = value;
}

void settings::Settings::set_snake_units(int value) {
	this->snake_units = value;
}

void settings::Settings::set_obs_no(int value) {
	this->obs_no = value;
}

void settings::Settings::set_head_centre_x(int value) {
	this->head_centre_x = value;
}

void settings::Settings::set_head_centre_y(int value) {
	this->head_centre_y = value;
}

void settings::Settings::set_head_dir(snake_node::direction_e value) {
	this->head_dir = value;
}

void settings::Settings::set_snake_color(graphics_utils::palette_e new_color) {
	this->snake_color = new_color;
}

void settings::Settings::set_obs_color(graphics_utils::palette_e new_color) {
	this->obs_color = new_color;
}

void settings::Settings::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Snake Game settings:\n\tHard Wall: ", this->hard_wall, "\n\tSave fiename: ", this->save_filename, "\n\tNumber of obstacles: ", this->obs_no, "\n\tNumber of snake units: ", this->snake_units, "\n\tNode Dimensions: Height->", this->node_height, " Width->", this->node_width, "\n\tSpeed Settings (Unit: pixel/iteration): Current speed->", this->speed, " Speed Increment->", this->speed_incr, "\n\tHead Position: X->", this->head_centre_x, " Y->", this->head_centre_y, "\n\tHead direction: ", this->head_dir, "\n\tColouring: Snake->", this->snake_color, " Obstacles->", this->obs_color);
}

settings::Settings::~Settings() {
//	std::string pretext ("Settings Destructor");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}
