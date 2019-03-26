/**
 * @copyright
 * @file obstacle_list.cpp
 * @author Andrea Gianarda
 * @date 24th March 2019
 * @brief Obstacle List function
 */

#include <iostream>
#include <cmath>

#include "graphics_utils.h"
#include "obstacle_list.h"
#include "obstacle.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace obstacle_list;
using namespace obstacle;
using namespace graphics_utils;

obstacle_list::ObstacleList::~ObstacleList() {

	std::string pretext ("Obstacle List Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	obstacle::ObstacleNode * node_ptr = this->get_head();
	while (node_ptr != nullptr) {
		obstacle::ObstacleNode * node_ptr_tmp = node_ptr;
		node_ptr->print_info(logging::verb_level_e::LOW, pretext);
		node_ptr = node_ptr->get_next();
		node_ptr_tmp->~ObstacleNode();
	}
	LOG_INFO(logging::verb_level_e::HIGH, "Obstacle list destroyed");

}
