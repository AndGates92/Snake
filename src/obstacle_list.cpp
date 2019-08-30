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

using namespace std;
using namespace logging;
using namespace obstacle_list;
using namespace obstacle;
using namespace colours;

obstacle_list::ObstacleList::~ObstacleList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	this->~BasicObjList();

	LOG_INFO(logging::verb_level_e::HIGH, "Obstacle list destroyed");

}

void obstacle_list::ObstacleList::add_element(int centre_x, int centre_y, int obstacle_width, int obstacle_height, colours::palette_e obstacle_colour) {

	std::string name = this->get_name();
	std::vector<obstacle::Obstacle>* obs_vector = &(this->get_head());

	LOG_INFO(logging::verb_level_e::LOW, "[Add Object] Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", obstacle_width, ", height ", obstacle_height, " colour ", obstacle_colour, ".");
	obstacle::Obstacle new_obstacle = obstacle::Obstacle(name, centre_x, centre_y, obstacle_width, obstacle_height, obstacle_colour);

	obs_vector->insert(obs_vector->begin(), new_obstacle);
}
