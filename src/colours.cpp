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

// Convert string to object type colour_e
colours::palette_e colours::str_to_colour (std::string colour) {

	colours::palette_e colour_tmp = colours::palette_e::UNKNOWN;

	if ((colour.compare("RED") == 0) | (colour.compare("Up")) | (colour.compare("up"))) {
		colour_tmp = colours::palette_e::RED;
	} else if ((colour.compare("BLUE") == 0) | (colour.compare("Blue")) | (colour.compare("blue"))) {
		colour_tmp = colours::palette_e::BLUE;
	} else if ((colour.compare("GREEN") == 0) | (colour.compare("Green")) | (colour.compare("green"))) {
		colour_tmp = colours::palette_e::GREEN;
	} else if ((colour.compare("YELLOW") == 0) | (colour.compare("Yellow")) | (colour.compare("yellow"))) {
		colour_tmp = colours::palette_e::YELLOW;
	} else if ((colour.compare("PURPLE") == 0) | (colour.compare("Purple")) | (colour.compare("purple"))) {
		colour_tmp = colours::palette_e::PURPLE;
	} else if ((colour.compare("PINK") == 0) | (colour.compare("Pink")) | (colour.compare("pink"))) {
		colour_tmp = colours::palette_e::PINK;
	} else if ((colour.compare("BROWN") == 0) | (colour.compare("Brown")) | (colour.compare("brown"))) {
		colour_tmp = colours::palette_e::BROWN;
	} else if ((colour.compare("WHITE") == 0) | (colour.compare("White")) | (colour.compare("white"))) {
		colour_tmp = colours::palette_e::WHITE;
	} else if ((colour.compare("BLACK") == 0) | (colour.compare("Black")) | (colour.compare("black"))) {
		colour_tmp = colours::palette_e::BLACK;
	} else if ((colour.compare("UNKNOWN") == 0) | (colour.compare("Unknown")) | (colour.compare("unknown"))) {
		colour_tmp = colours::palette_e::UNKNOWN;
	} else {
		colour_tmp = colours::palette_e::UNKNOWN;
		LOG_ERROR("Unknown palette: ", colour);
	}

	return colour_tmp;
}
