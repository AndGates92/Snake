/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>

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
