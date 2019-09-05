/**
 * @copyright
 * @file settings.cpp
 * @author Andrea Gianarda
 * @date 17th April 2019
 * @brief Settings function
 */

#include <iostream>

#include "settings.h"
#include "colours.h"
#include "logging.h"
#include "snake_utils.h"

settings::Settings snake_settings;

// ================================================================
// Get functions
// ================================================================
bool settings::Settings::get_auto_ride_flag() {
	return this->auto_ride;
}

bool settings::Settings::get_hard_wall_flag() {
	return this->hard_wall;
}

std::string settings::Settings::get_dump_filename() {
	return this->dump_filename;
}

std::string settings::Settings::get_save_filename() {
	return this->save_filename;
}

settings::game_status_e settings::Settings::get_game_status() {
	return this->game_status;
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

int settings::Settings::get_tile_width() {
	return this->tile_width;
}

int settings::Settings::get_tile_height() {
	return this->tile_height;
}

snake_utils::direction_e settings::Settings::get_head_dir() {
	return this->head_dir;
}

colours::palette_e settings::Settings::get_snake_colour() {
	return this->snake_colour;
}

colours::palette_e settings::Settings::get_obs_colour() {
	return this->obs_colour;
}

int settings::Settings::get_score() {
	return this->score;
}

// ================================================================
// Set functions
// ================================================================
void settings::Settings::set_auto_ride_flag(bool value) {
	this->auto_ride = value;
}

void settings::Settings::set_hard_wall_flag(bool value) {
	this->hard_wall = value;
}

void settings::Settings::set_dump_filename(std::string name) {
	this->dump_filename = name;
}

void settings::Settings::set_save_filename(std::string name) {
	this->save_filename = name;
}

void settings::Settings::set_game_status(settings::game_status_e game_status_new) {
	this->game_status = game_status_new;
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

void settings::Settings::set_tile_width(int value) {
	this->tile_width = value;
}

void settings::Settings::set_tile_height(int value) {
	this->tile_height = value;
}

void settings::Settings::set_head_dir(snake_utils::direction_e value) {
	this->head_dir = value;
}

void settings::Settings::set_snake_colour(colours::palette_e new_colour) {
	this->snake_colour = new_colour;
}

void settings::Settings::set_obs_colour(colours::palette_e new_colour) {
	this->obs_colour = new_colour;
}

void settings::Settings::set_score(int value) {
	this->score = value;
}

void settings::Settings::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Snake Game settings: Status: ", this->game_status, "\n\tAutomatic Ride: ", this->auto_ride, "\n\tHard Wall: ", this->hard_wall, "\n\tOutput files: save->", this->save_filename, " dump->", this->dump_filename, "\n\tNumber of obstacles: ", this->obs_no, "\n\tNumber of snake units: ", this->snake_units, "\n\tNode Dimensions: Height->", this->node_height, " Width->", this->node_width, "\n\tSpeed Settings (Unit: pixel/iteration): Current speed->", this->speed, " Speed Increment->", this->speed_incr, "\n\tHead Position: X->", this->head_centre_x, " Y->", this->head_centre_y, "\n\tHead direction: ", this->head_dir, "\n\tColouring: Snake->", this->snake_colour, " Obstacles->", this->obs_colour, "\n\tStat window Tile Dimensions: Height->", this->tile_height, " Width->", this->tile_width, "\n\tScore->", this->score);
}

settings::Settings::~Settings() {
//	std::string pretext ("Settings Destructor");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}

void settings::Settings::save_data(iofile::File & savefile) {
	savefile.write_ofile("Type: Settings\n");
	savefile.write_ofile("Dump: ", this->dump_filename, "\n");
	savefile.write_ofile("Save: ", this->save_filename, "\n");
	savefile.write_ofile("Speed: ", this->speed, "\n");
	savefile.write_ofile("Automatic ride: ", this->auto_ride, "\n");
	savefile.write_ofile("Wall: ", this->hard_wall, "\n");
	int snake_units = this->snake_units;
	savefile.write_ofile("SnakeUnits: ", snake_units, "\n");
	int obs_no = this->obs_no;
	savefile.write_ofile("Obstacles: ", obs_no, "\n");
	savefile.write_ofile("Score: ", this->score, "\n");
	savefile.write_ofile("\n");

	savefile.write_ofile("//******************************\n");
	savefile.write_ofile("// Stat Windows\n");
	savefile.write_ofile("//******************************\n");
	savefile.write_ofile("Type: Tile\n");
	savefile.write_ofile("Width: ", this->tile_width, "\n");
	savefile.write_ofile("Height: ", this->tile_height, "\n");
	savefile.write_ofile("\n");
}

// ================================================================
// Overload << operator for game_status_e
// ================================================================
std::ostream& settings::operator<< (std::ostream& os, settings::game_status_e game_status) {

	switch (game_status) {
		case settings::game_status_e::RUNNING:
			os << "RUNNING";
			break;
		case settings::game_status_e::PAUSED:
			os << "PAUSED";
			break;
		default:
			os << "Unknown game status";
			break;
	}

	return os;
}

