/**
 * @copyright
 * @file char_lut.cpp
 * @author Andrea Gianarda
 * @date 29th April 2019
 * @brief Number template functions
 */

#include <iostream>

#include "logging.h"
#include "char_lut.h"

using namespace std;
using namespace logging;
using namespace char_lut;

const bool * char_lut::get_char_tiles(const char & char_s) {

	const bool * char_tiles = NULL;

	switch (char_s) {
		case '0':
			char_tiles = char_lut::number_zero;
			break;
		case '1':
			char_tiles = char_lut::number_one;
			break;
		case '2':
			char_tiles = char_lut::number_two;
			break;
		case '3':
			char_tiles = char_lut::number_three;
			break;
		case '4':
			char_tiles = char_lut::number_four;
			break;
		case '5':
			char_tiles = char_lut::number_five;
			break;
		case '6':
			char_tiles = char_lut::number_six;
			break;
		case '7':
			char_tiles = char_lut::number_seven;
			break;
		case '8':
			char_tiles = char_lut::number_eight;
			break;
		case '9':
			char_tiles = char_lut::number_nine;
			break;
		default :
			LOG_ERROR("Unknown character: ", char_s);
			break;
	}

	return char_tiles;
}
