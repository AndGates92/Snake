/**
 * @copyright
 * @file snake_direction.cpp
 * @author Andrea Gianarda
 * @date 2nd July 2019
 * @brief Snake Direction List Class function
 */

#include <iostream>

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
