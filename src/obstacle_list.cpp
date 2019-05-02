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

void obstacle_list::ObstacleList::add_node(int centre_x, int centre_y, int ostacle_width, int ostacle_height, colours::palette_e ostacle_colour) {

	std::string name = this->get_name();
	obstacle::ObstacleNode * head = this->get_head();

	LOG_INFO(logging::verb_level_e::LOW, "[Add Object] Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", ostacle_width, ", height ", ostacle_height, " colour ", ostacle_colour, ".");
	obstacle::ObstacleNode * new_obstacle = new obstacle::ObstacleNode(name, centre_x, centre_y, ostacle_width, ostacle_height, ostacle_colour);
	if (new_obstacle == nullptr) {
		LOG_ERROR("Can't allocate memory for obstacle Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", ostacle_width, ", height ", ostacle_height, " colour ", ostacle_colour, ".");
	}
	new_obstacle->set_prev(nullptr);
	new_obstacle->set_next(head);
	if (head != nullptr) {
		head->set_prev(new_obstacle);
	}
	this->set_head(new_obstacle);
}
