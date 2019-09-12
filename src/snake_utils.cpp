/**
 * @copyright
 * @file snake_utils.cpp
 * @author Andrea Gianarda
 * @date 09th May 2019
 * @brief Snake utility function
 */

#include "snake_utils.h"
#include "logging.h"

// ================================================================
// Overload << operator for direction_e
// ================================================================
std::ostream& snake_utils::operator<< (std::ostream& os, const snake_utils::direction_e & direction) {

	switch (direction) {
		case snake_utils::direction_e::UP:
			os << "UP";
			break;
		case snake_utils::direction_e::DOWN:
			os << "DOWN";
			break;
		case snake_utils::direction_e::LEFT:
			os << "LEFT";
			break;
		case snake_utils::direction_e::RIGHT:
			os << "RIGHT";
			break;
		case snake_utils::direction_e::UNKNOWN:
			os << "UNKNOWN";
			break;
		default:
			os << "Unknown direction";
			break;
	}

	return os;
}

// Convert string to object type direction_e
snake_utils::direction_e snake_utils::str_to_direction (std::string dir) {

	snake_utils::direction_e dir_tmp(snake_utils::direction_e::UNKNOWN);

	if ((dir.compare("UP") == 0) || (dir.compare("Up") == 0) || (dir.compare("up") == 0)) {
		dir_tmp = snake_utils::direction_e::UP;
	} else if ((dir.compare("DOWN") == 0) || (dir.compare("Down") == 0) || (dir.compare("down") == 0)) {
		dir_tmp = snake_utils::direction_e::DOWN;
	} else if ((dir.compare("LEFT") == 0) || (dir.compare("Left") == 0) || (dir.compare("left") == 0)) {
		dir_tmp = snake_utils::direction_e::LEFT;
	} else if ((dir.compare("RIGHT") == 0) || (dir.compare("Right") == 0) || (dir.compare("right") == 0)) {
		dir_tmp = snake_utils::direction_e::RIGHT;
	} else if ((dir.compare("UNKNOWN") == 0) || (dir.compare("Unknown") == 0) || (dir.compare("unknown") == 0)) {
		dir_tmp = snake_utils::direction_e::UNKNOWN;
	} else {
		dir_tmp = snake_utils::direction_e::UNKNOWN;
		LOG_ERROR("Unknown direction: ", dir);
	}

	return dir_tmp;
}
