/**
 * @copyright
 * @file snake_direction.cpp
 * @author Andrea Gianarda
 * @date 2nd July 2019
 * @brief Snake Direction List Class function
 */

#include <iostream>

#include "snake_utils.h"
#include "snake_direction.h"
#include "snake_direction_list.h"
#include "logging.h"

using namespace std;
using namespace snake_direction_list;
using namespace logging;

// ================================================================
// Destructor
// ================================================================
snake_direction_list::SnakeDirectionList::~SnakeDirectionList() {
	std::string pretext ("");
	this->print_info(logging::verb_level_e::LOW, pretext);
}


void snake_direction_list::SnakeDirectionList::add_node(snake_utils::direction_e direction) {

	snake_direction::SnakeDirectionNode * head_dir(this->get_head());

	LOG_INFO(logging::verb_level_e::LOW, "[Add node] Create node with direction ", direction);
	snake_direction::SnakeDirectionNode * new_dir = new snake_direction::SnakeDirectionNode(direction);
	if (new_dir == nullptr) {
		LOG_ERROR("Can't allocate memory for direction node");
	}

	new_dir->set_prev(nullptr);

	if(head_dir != nullptr) {
		head_dir->set_prev(new_dir);
	}

	new_dir->set_next(head_dir);
	this->set_head(new_dir);

}
