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

const bool * char_lut::get_char_tiles(const char & char_print) {

	const bool * char_tiles = NULL;

	switch (char_print) {
		case 'C':
		case 'c':
			char_tiles = char_lut::char_c;
			break;
		case 'E':
		case 'e':
			char_tiles = char_lut::char_e;
			break;
		case 'O':
		case 'o':
			char_tiles = char_lut::char_o;
			break;
		case 'R':
		case 'r':
			char_tiles = char_lut::char_r;
			break;
		case 'S':
		case 's':
			char_tiles = char_lut::char_s;
			break;
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
		case '=':
			char_tiles = char_lut::char_eq;
			break;
		case ':':
			char_tiles = char_lut::char_colon;
			break;
		default :
			LOG_ERROR("Unknown character: ", char_print);
			break;
	}

	return char_tiles;
}
