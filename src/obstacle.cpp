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
	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void obstacle::Obstacle::print_info(logging::verb_level_e verbosity, std::string pretext) {
	basic_object::BasicObject::print_info(verbosity, pretext);
}

// ================================================================
// Obstacle Node
// ================================================================
obstacle::ObstacleNode::~ObstacleNode() {
	std::string pretext ("Obstacle Node Destructor");
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
