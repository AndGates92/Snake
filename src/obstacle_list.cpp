/**
 * @copyright
 * @file obstacle_list.cpp
 * @author Andrea Gianarda
 * @date 24th March 2019
 * @brief Obstacle List function
 */

#include <iostream>
#include <cmath>

#include "game_graphics.h"
#include "graphics_utils.h"
#include "obstacle_list.h"
#include "obstacle.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace obstacle_list;
using namespace obstacle;
using namespace graphics_utils;
using namespace game_graphics;

obstacle_list::ObstacleList::~ObstacleList() {

	std::string pretext ("Obstacle List Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	obstacle::ObstacleNode * node_ptr = this->head;
	while (this->head != nullptr) {
		node_ptr = this->head;
		node_ptr->print_info(logging::verb_level_e::LOW, pretext);
		this->head = this->head->get_next();
		node_ptr->~ObstacleNode();
	}
	LOG_INFO(logging::verb_level_e::HIGH, "Obstacle list destroyed");

}


void obstacle_list::ObstacleList::add_node(int centre_x, int centre_y, int obstacle_width, int obstacle_height, graphics_utils::palette_e obstacle_colour) {

	LOG_INFO(logging::verb_level_e::LOW, "[Add Node] Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", obstacle_width, ", height ", obstacle_height, " colour ", obstacle_colour, ".");
	obstacle::ObstacleNode * new_obstacle = new obstacle::ObstacleNode(centre_x, centre_y, obstacle_width, obstacle_height, obstacle_colour);

	new_obstacle->set_prev(nullptr);
	new_obstacle->set_next(this->head);
	if (this->head != nullptr) {
		this->head->set_prev(new_obstacle);
	}
	this->head = new_obstacle;

}

void obstacle_list::ObstacleList::remove_node(obstacle::ObstacleNode * & node) {
	obstacle::ObstacleNode * node_saved = node;

	if (node == this->head) {
		// Move head pointer as obstacle list to delete is the head
		if (node->get_next() == nullptr) {
			this->head = nullptr;
		} else {
			this->head = this->head->get_next();
			this->head->get_prev() = nullptr;
		}
	} else {
		node->get_prev()->get_next() = node->get_next();
		if (node->get_next() != nullptr) {
			node->get_next()->get_prev() = node->get_prev();
		}
	}

	node_saved->~ObstacleNode();
}

void obstacle_list::ObstacleList::print_info(logging::verb_level_e verbosity, std::string pretext) {
	obstacle::ObstacleNode * obstacle_list = this->head;

	while (obstacle_list != nullptr) {
		obstacle_list->print_info(verbosity, pretext);
		obstacle_list = obstacle_list->get_next();
	}
}
