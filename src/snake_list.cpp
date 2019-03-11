/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>
#include <cmath>

#include "graphics_utils.h"
#include "snake_list.h"
#include "snake_node.h"
#include "log.h"

using namespace std;
using namespace log;
using namespace snake_list;
using namespace snake_node;

snake_list::SnakeList::~SnakeList() {

	std::string pretext ("Snake List Destructor");
	this->print_info(log::verb_level_e::LOW, pretext);

	snake_node::SnakeNode * node_ptr = nullptr;
	while (this->head != nullptr) {
		node_ptr = this->head;
		this->head = this->head->get_next();
		node_ptr->~SnakeNode();
		delete [] node_ptr;
	}
	LOG_INFO(log::verb_level_e::HIGH, "Snake list destroyed");

}


void snake_list::SnakeList::add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour) {

	LOG_INFO(log::verb_level_e::LOW, "[Add Node] Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	snake_node::SnakeNode * new_snake = new snake_node::SnakeNode(centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour);

	new_snake->set_prev(nullptr);

	if(this->head != nullptr) {
		this->head->set_prev(new_snake);
	}

	new_snake->set_next(this->head);
	this->head = new_snake;

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

void snake_list::SnakeList::print_info(log::verb_level_e verbosity, std::string pretext) {
	snake_node::SnakeNode * snake_list = this->head;

	while (snake_list != nullptr) {
		snake_list->print_info(verbosity, pretext);
		snake_list = snake_list->get_next();
	}
}

void snake_list::SnakeList::move(int increment, int win_width, int win_height) {
	snake_node::SnakeNode * snake_list = this->head;
	snake_node::SnakeNode * snake_list_prev = this->head;

	snake_node::direction_e direction_prev = this->head->get_direction();
	int x_centre_prev = this->head->get_x_centre();
	int y_centre_prev = this->head->get_y_centre();
	int width_prev = this->head->get_width();
	int height_prev = this->head->get_height();

	snake_node::direction_e direction_curr = this->head->get_direction();
	int x_centre_curr = this->head->get_x_centre();
	int y_centre_curr = this->head->get_y_centre();
	int width_curr = this->head->get_width();
	int height_curr = this->head->get_height();

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

		// if get_prev == nullptr means that we are looking at the 1st element in linked list
		if (snake_list->get_prev() != nullptr) {
			int distance_units = 0;
			int distance_measured = 0;
			// Check distance between units is correct
			if ((direction_curr == snake_node::direction_e::RIGHT) | (direction_curr == snake_node::direction_e::LEFT)) {
				distance_units = (width_prev/2) + (width_curr/2);
				distance_measured = ((int) abs(x_centre_prev - x_centre_curr));
cout << "X prev " << x_centre_prev << " X curr " << x_centre_curr << " ditance " << distance_units << endl;
				ASSERT((x_centre_prev - x_centre_curr) == distance_units)
			} else if ((direction_curr == snake_node::direction_e::UP) | (direction_curr == snake_node::direction_e::DOWN)) {
				distance_units = (height_prev/2) + (height_curr/2);
				distance_measured = ((int) abs(y_centre_prev - y_centre_curr));
cout << "Y prev " << x_centre_prev << " Y curr " << x_centre_curr << " ditance " << distance_units << endl;
			} else {
				LOG_ERROR("Unknown direction")
			}
			ASSERT(distance_measured  == distance_units)
		}

		snake_list->move(increment, win_width, win_height);

		if (direction_prev == direction_curr) {
			snake_list_prev->set_direction(direction_curr);
		}

		snake_list_prev = snake_list;
		snake_list = snake_list->get_next();
	}
}

snake_node::direction_e snake_list::SnakeList::get_head_direction() {

	snake_node::SnakeNode * snake_list = this->head;
	snake_node::direction_e direction = this->head->get_direction();

	while (snake_list != nullptr) {
		direction = snake_list->get_direction();
		snake_list = snake_list->get_next();
	}

	return direction;
}


void snake_list::SnakeList::set_head_direction(snake_node::direction_e direction) {

	snake_node::SnakeNode * snake_list = this->head;

	while (snake_list->get_next() != nullptr) {
		snake_list = snake_list->get_next();
	}


	snake_list->set_direction(direction);
}
