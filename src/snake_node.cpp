/**
 * @copyright
 * @file snake_node.cpp
 * @author Andrea Gianarda
 * @date 5th March 2019
 * @brief Snake node functions
 */

#include <string>
#include <iostream>
#include <fstream>

#include "log.h"
#include "snake_node.h"
#include "snake_unit.h"

using namespace std;
using namespace log;
using namespace snake_unit;
using namespace snake_node;

snake_node::SnakeNode::~SnakeNode() {
	std::string pretext ("Snake Node Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);
	this->node.~SnakeUnit();
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

snake_unit::SnakeUnit snake_node::SnakeNode::get_node() {
	std::string pretext ("Get current node");
	this->node.print_info(log::verb_level_e::DEBUG, pretext);
	return this->node;
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

void snake_node::SnakeNode::set_node(snake_unit::SnakeUnit node) {
	this->node = node;
}


void snake_node::SnakeNode::print_info(log::verb_level_e verbosity, std::string pretext) {
	this->node.print_info(verbosity, pretext);
}
