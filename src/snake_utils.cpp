/**
 * @copyright
 * @file snake_utils.cpp
 * @author Andrea Gianarda
 * @date 09th May 2019
 * @brief Snake utility function
 */

#include "snake_utils.h"

// ================================================================
// Overload << operator for direction_e
// ================================================================
std::ostream& snake_utils::operator<< (std::ostream& os, snake_utils::direction_e direction) {

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


