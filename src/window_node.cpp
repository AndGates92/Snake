/**
 * @copyright
 * @file window_node.cpp
 * @author Andrea Gianarda
 * @date 18th February 2019
 * @brief Window node functions
 */

#include <string>
#include <iostream>
#include <fstream>

#include "log.h"
#include "window_node.h"
#include "window_obj.h"

using namespace std;
using namespace log;
using namespace window_obj;
using namespace window_node;

void window_node::WindowNode::destroy_node() {
	this->obj.destroy_obj();
}

window_node::WindowNode::~WindowNode() {
	std::string pretext ("Window Node Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
	this->obj.~WindowObj();
}

// ================================================================
// Get functions
// ================================================================

window_node::WindowNode * & window_node::WindowNode::get_next() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer next: ", this->next);
	return this->next;
}

window_node::WindowNode * & window_node::WindowNode::get_prev() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer prev: ", this->prev);
	return this->prev;
}

window_obj::WindowObj window_node::WindowNode::get_obj() {
	std::string pretext ("Get current obj");
	this->obj.print_info(log::verb_level_e::DEBUG, pretext);
	return this->obj;
}

// ================================================================
// Set functions
// ================================================================

void window_node::WindowNode::set_next(window_node::WindowNode * next_ptr) {
	this->next = next_ptr;
}

void window_node::WindowNode::set_prev(window_node::WindowNode * prev_ptr) {
	this->prev = prev_ptr;
}

void window_node::WindowNode::set_obj(window_obj::WindowObj obj) {
	this->obj = obj;
}


void window_node::WindowNode::print_info(log::verb_level_e verbosity, std::string pretext) {
	this->obj.print_info(verbosity, pretext);
}
