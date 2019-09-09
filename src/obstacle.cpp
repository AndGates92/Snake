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
#include "basic_object.h"

// ================================================================
// Destructor
// ================================================================
obstacle::Obstacle::~Obstacle() {
	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void obstacle::Obstacle::print_info(logging::verb_level_e verbosity, std::string pretext) {
	std::string type = this->get_type();
	LOG_INFO(verbosity, "[", type, " ", pretext, "] ", this, ".");
}
