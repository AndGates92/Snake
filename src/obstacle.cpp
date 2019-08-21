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
