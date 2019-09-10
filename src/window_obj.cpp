/**
 * @copyright
 * @file window_list.cpp
 * @author Andrea Gianarda
 * @date 13th February 2019
 * @brief File function
 */

#include <iostream>

#include "window_obj.h"
#include "menu.h"
#include "window.h"
#include "logging.h"

void window_obj::WindowObj::destroy_obj() {
	std::string pretext ("Destroy Window Object");
	this->print_info(logging::verb_level_e::HIGH, pretext);
	this->drawing.destroy_window();
	this->action_list.destroy_menu();
}

window_obj::WindowObj::~WindowObj() {
	std::string pretext ("Window Object Destructor");
	this->print_info(logging::verb_level_e::HIGH, pretext);
	this->drawing.~Window();
	this->action_list.~Menu();
}

void window_obj::WindowObj::print_info(logging::verb_level_e verbosity, std::string pretext) {
	// Window content
	std::string pretext_drawing (pretext);
	pretext_drawing.append(" (Drawing)");
	this->drawing.print_info(verbosity, pretext_drawing);
	// Menu
	std::string pretext_menu (pretext);
	pretext_menu.append(" (Menu)");
	this->action_list.print_info(verbosity, pretext_menu);
}

window::Window window_obj::WindowObj::get_window() const {
	return this->drawing;
}

int window_obj::WindowObj::get_win_id() const {
	return this->drawing.get_id();
}

std::string window_obj::WindowObj::get_win_title() const {
	return this->drawing.get_title();
}

int window_obj::WindowObj::get_menu_id() const {
	return this->action_list.get_id();
}

colours::palette_e window_obj::WindowObj::get_colour_bg() const {
	return this->drawing.get_colour();
}

menu::Menu window_obj::WindowObj::get_menu() const {
	return this->action_list;
}

void window_obj::WindowObj::save_data (iofile::File & savefile) {
	drawing.save_data(savefile);
	action_list.save_data(savefile);
}

bool window_obj::WindowObj::operator== (const window_obj::WindowObj & rhs) {
	return ((this->drawing == rhs.drawing) && (this->action_list == rhs.action_list));
}

bool window_obj::WindowObj::operator!= (const window_obj::WindowObj & rhs) {
	return ((this->drawing != rhs.drawing) && (this->action_list != rhs.action_list));
}

std::ostream& window_obj::operator<< (std::ostream& os, const window_obj::WindowObj & window_object) {
	os << "Drawing " << window_object.get_window() << " Menu " << window_object.get_menu();
	return os;
}
