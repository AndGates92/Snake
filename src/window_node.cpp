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


window_node::WindowNode::~WindowNode() {
	LOG_INFO(log::verb_level_e::HIGH, "Window node destroyed");
	node.~WindowObj();
}

window_node::WindowNode * window_node::WindowNode::get_prev() {
	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer next", this->next);
	return this->next;
}

window_obj::WindowObj window_node::WindowNode::get_node() {
	this->node.print_info(log::verb_level_e::DEBUG, "Get current node");
	return this->node;
}

window_node::WindowNode * window_node::WindowNode::get_next() {

	LOG_INFO(log::verb_level_e::DEBUG, "Get pointer prev", this->prev);
	return this->prev;

}

void window_node::WindowNode::set_next(window_node::WindowNode * next_ptr) {
	this->next = next_ptr;
}

void window_node::WindowNode::set_prev(window_node::WindowNode * prev_ptr) {
	this->prev = prev_ptr;
}

void window_node::WindowNode::set_node(window_obj::WindowObj node) {
	this->node = node;
}


void window_node::WindowNode::print_info(log::verb_level_e verbosity, std::string pretext) {
	window_node::WindowNode::node.print_info(verbosity, pretext);
}
