/**
 * @copyright
 * @file colours.cpp
 * @author Andrea Gianarda
 * @date 2nd of May 2019
 * @brief Colours functions
 */

#include <iostream>

#include "colours.h"

// Overload << operator for palette_e
std::ostream& colours::operator<< (std::ostream& os, colours::palette_e palette) {

	switch (palette) {
		case colours::palette_e::RED:
			os << "RED";
			break;
		case colours::palette_e::BLUE:
			os << "BLUE";
			break;
		case colours::palette_e::GREEN:
			os << "GREEN";
			break;
		case colours::palette_e::YELLOW:
			os << "YELLOW";
			break;
		case colours::palette_e::PURPLE:
			os << "PURPLE";
			break;
		case colours::palette_e::PINK:
			os << "PINK";
			break;
		case colours::palette_e::BROWN:
			os << "BROWN";
			break;
		case colours::palette_e::WHITE:
			os << "WHITE";
			break;
		case colours::palette_e::BLACK:
			os << "BLACK";
			break;
		case colours::palette_e::UNKNOWN:
			os << "UNKNOWN";
			break;
		default:
			os << "Unknown colour";
			break;
	}

	return os;
}
