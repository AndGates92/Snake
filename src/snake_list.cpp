/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>
#include <cmath>

#include "game_graphics.h"
#include "graphics_utils.h"
#include "snake_list.h"
#include "snake_node.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace snake_list;
using namespace snake_node;
using namespace graphics_utils;
using namespace game_graphics;

snake_list::SnakeList::~SnakeList() {

	std::string pretext ("Snake List Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	snake_node::SnakeNode * node_ptr = this->head;
	while (this->head != nullptr) {
		node_ptr = this->head;
		node_ptr->print_info(logging::verb_level_e::LOW, pretext);
		this->head = this->head->get_next();
		node_ptr->~SnakeNode();
	}
	LOG_INFO(logging::verb_level_e::HIGH, "Snake list destroyed");

}


void snake_list::SnakeList::add_node(std::string name, int centre_x, int centre_y, int snake_width, int snake_height, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour) {

	LOG_INFO(logging::verb_level_e::LOW, "[Add Node] Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	snake_node::SnakeNode * new_snake = new snake_node::SnakeNode(name, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour);

	if(this->head != nullptr) {
		snake_node::SnakeNode * snake_list = this->head;
		snake_node::SnakeNode * snake_found = nullptr;

		int width_head = this->head->get_width();
		ASSERT(width_head == snake_width)

		int height_head = this->head->get_height();
		ASSERT(height_head == snake_height)



		while (snake_list != nullptr) {
			int prev_x = 0;
			int prev_y = 0;

			int curr_x = snake_list->get_x_centre();
			int curr_y = snake_list->get_y_centre();

			if (snake_list->get_prev() != nullptr) {
				prev_x = snake_list->get_prev()->get_x_centre();
				prev_y = snake_list->get_prev()->get_y_centre();

				if ((((int) abs(curr_x - centre_x)) <= snake_width) && (((int) abs(prev_x - centre_x)) <= snake_width) && (((int) abs(curr_y - centre_y)) <= snake_height) && (((int) abs(prev_y - centre_y)) <= snake_height)) {
					snake_found = snake_list;
				}
			}
			snake_list = snake_list->get_next();
		}

		if (snake_found == nullptr) {
			snake_node::SnakeNode * snake_head = this->head;

			new_snake->set_next(snake_head);
			new_snake->set_prev(nullptr);
			snake_head->set_prev(new_snake);

			if (snake_head == this->head) {
				this->head = new_snake;
			}
		} else {
			int width_found = snake_found->get_width();
			ASSERT(width_found == snake_width)

			int height_found = snake_found->get_height();
			ASSERT(height_found == snake_height)

			snake_node::direction_e direction_found = snake_found->get_direction();
			ASSERT(direction_found == snake_direction)

			int x_centre_found = snake_found->get_x_centre();
			int y_centre_found = snake_found->get_y_centre();

			int hdistance_units = 0;
			int hdistance_measured = 0;
			int vdistance_units = 0;
			int vdistance_measured = 0;
			if ((direction_found == snake_node::direction_e::RIGHT) | (direction_found == snake_node::direction_e::LEFT)) {
				hdistance_units = (snake_width/2) + (width_found/2);
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = 0;
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			} else if ((direction_found == snake_node::direction_e::UP) | (direction_found == snake_node::direction_e::DOWN)) {
				hdistance_units = 0;
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = (snake_height/2) + (height_found/2);
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			}

			ASSERT(hdistance_units == hdistance_measured)
			ASSERT(vdistance_units == vdistance_measured)

			new_snake->set_prev(snake_found->get_prev());
			new_snake->set_next(snake_found);
			snake_found->set_prev(new_snake);
			snake_found->get_prev()->set_next(new_snake);
		}
	} else {
		new_snake->set_prev(nullptr);
		new_snake->set_next(nullptr);
		this->head = new_snake;
	}

}

void snake_list::SnakeList::remove_node(snake_node::SnakeNode * & node) {
	snake_node::SnakeNode * node_saved = node;

	if (node == this->head) {
		// Move head pointer as snake list to delete is the head
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

	node_saved->~SnakeNode();
}

void snake_list::SnakeList::print_info(logging::verb_level_e verbosity, std::string pretext) {
	snake_node::SnakeNode * snake_list = this->head;

	while (snake_list != nullptr) {
		snake_list->print_info(verbosity, pretext);
		snake_list = snake_list->get_next();
	}
}

void snake_list::SnakeList::move(int speed, int win_width, int win_height) {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Window dimensions: Width ", win_width, " Height ", win_height, " Speed: ", speed);
	snake_node::SnakeNode * snake_list = this->head;

	snake_node::direction_e direction_prev = this->head->get_direction();
	int x_centre_prev = this->head->get_x_centre();
	int y_centre_prev = this->head->get_y_centre();
	int height_prev = this->head->get_height();
	int width_prev = this->head->get_width();

	snake_node::direction_e direction_curr = this->head->get_direction();
	int x_centre_curr = this->head->get_x_centre();
	int y_centre_curr = this->head->get_y_centre();
	int height_curr = this->head->get_height();
	int width_curr = this->head->get_width();

	while (snake_list != nullptr) {

		// Store values of previous element
		direction_prev = direction_curr;
		x_centre_prev = x_centre_curr;
		y_centre_prev = y_centre_curr;
		height_prev = height_curr;
		width_prev = width_curr;

		direction_curr = snake_list->get_direction();
		x_centre_curr = snake_list->get_x_centre();
		y_centre_curr = snake_list->get_y_centre();
		height_curr = snake_list->get_height();
		width_curr = snake_list->get_width();

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Current Unit: X ", x_centre_curr, " Y ", y_centre_curr, " Direction ", direction_curr);
		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Previous Unit: X ", x_centre_prev, " Y ", y_centre_prev, " Direction ", direction_prev);

		if (direction_prev != direction_curr) {
			int sign = 0;
			if ((direction_prev == snake_node::direction_e::UP) | (direction_prev == snake_node::direction_e::RIGHT)) {
				sign = -1;
			} else {
				sign = 1;
			}

			int centre_distance = 0;
			int adjustment = 0;
			if (((direction_curr == snake_node::direction_e::RIGHT) | (direction_curr == snake_node::direction_e::LEFT)) & ((int) abs(x_centre_prev - x_centre_curr) < speed)) {
				centre_distance = ((height_curr + height_prev)/2);
				adjustment = centre_distance - ((int) abs(y_centre_curr - y_centre_prev));
				ASSERT(adjustment >= 0);
				int y_centre_adj = y_centre_curr + sign * adjustment;

				LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev,  " adjustment on Y ", adjustment, " New coordinates X ", x_centre_prev, " Y ", y_centre_adj);
				snake_list->set_direction(direction_prev);
				snake_list->set_x_centre(x_centre_prev);
				snake_list->set_y_centre(y_centre_adj);
				ASSERT((int) abs(y_centre_prev - y_centre_adj) == centre_distance);
			} else if (((direction_curr == snake_node::direction_e::UP) | (direction_curr == snake_node::direction_e::DOWN)) & ((int) abs(y_centre_prev - y_centre_curr) < speed)) {
				centre_distance = ((width_curr + width_prev)/2);
				adjustment = centre_distance - ((int) abs(x_centre_curr - x_centre_prev));
				ASSERT(adjustment >= 0);
				int x_centre_adj = x_centre_curr + sign * adjustment;

				LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev,  " adjustment on X ", adjustment, " New coordinates X ", x_centre_adj, " Y ", y_centre_prev);
				snake_list->set_direction(direction_prev);
				snake_list->set_x_centre(x_centre_adj);
				snake_list->set_y_centre(y_centre_prev);
				ASSERT((int) abs(x_centre_prev - x_centre_adj) == centre_distance);
			}
		}

		snake_list->move(speed, win_width, win_height);

		snake_list = snake_list->get_next();
	}
}

snake_node::SnakeNode * snake_list::SnakeList::get_head() {
	return this->head;
	}
