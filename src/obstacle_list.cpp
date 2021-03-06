/**
 * @copyright
 * @file obstacle_list.cpp
 * @author Andrea Gianarda
 * @date 24th March 2019
 * @brief Obstacle List function
 */

#include <iostream>
#include <cmath>

#include "colours.h"
#include "basic_obj_list.h"
#include "obstacle_list.h"
#include "obstacle.h"
#include "logging.h"

obstacle_list::ObstacleList::~ObstacleList() {

	LOG_INFO(logging::verb_level_e::DEBUG, "Obstacle list destructor");

}

void obstacle_list::ObstacleList::add_element(int centre_x, int centre_y, int obstacle_width, int obstacle_height, colours::palette_e obstacle_colour) {

	std::string name (this->get_name());
	std::vector<obstacle::Obstacle> & obs_vector (this->get_vector());

	obstacle::Obstacle new_obstacle(name, centre_x, centre_y, obstacle_width, obstacle_height, obstacle_colour);
	LOG_INFO(logging::verb_level_e::LOW, "[Add Obstacle] Name: ", name, new_obstacle, ".");

	obs_vector.insert(obs_vector.begin(), new_obstacle);
}
