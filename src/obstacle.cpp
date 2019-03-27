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
#include "basic_obj_node.h"

using namespace std;
using namespace obstacle;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
obstacle::Obstacle::~Obstacle() {
	LOG_INFO(logging::verb_level_e::LOW, "Obstacle Destructor")
//	std::string pretext ("Destructor");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}

void obstacle::Obstacle::print_info(logging::verb_level_e verbosity, std::string pretext) {
	basic_object::BasicObject::print_info(verbosity, pretext);
}

// ================================================================
// Obstacle Node
// ================================================================
obstacle::ObstacleNode::~ObstacleNode() {
	LOG_INFO(logging::verb_level_e::LOW, "Obstacle Node Destructor")
//	std::string pretext ("Destructor");
//	this->print_info(logging::verb_level_e::LOW, pretext);
}

void obstacle::ObstacleNode::print_info(logging::verb_level_e verbosity, std::string pretext) {
	Obstacle::print_info(verbosity, pretext);
	std::string name_pretext = this->get_name();
	name_pretext.append(" ");
	name_pretext.append(pretext);
	basic_obj_node::BasicObjNode<ObstacleNode>::print_info(verbosity, name_pretext);
}
