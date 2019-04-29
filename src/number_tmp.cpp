/**
 * @copyright
 * @file number_tmp.cpp
 * @author Andrea Gianarda
 * @date 29th April 2019
 * @brief Number template functions
 */

#include <iostream>

#include "logging.h"
#include "number_tmp.h"

using namespace std;
using namespace logging;
using namespace number_tmp;

const bool * number_tmp::get_digit_tiles(const char & digit) {

	const bool * digit_tiles = NULL;

	switch (digit) {
		case '0':
			digit_tiles = number_tmp::number_zero;
			break;
		case '1':
			digit_tiles = number_tmp::number_one;
			break;
		case '2':
			digit_tiles = number_tmp::number_two;
			break;
		case '3':
			digit_tiles = number_tmp::number_three;
			break;
		case '4':
			digit_tiles = number_tmp::number_four;
			break;
		case '5':
			digit_tiles = number_tmp::number_five;
			break;
		case '6':
			digit_tiles = number_tmp::number_six;
			break;
		case '7':
			digit_tiles = number_tmp::number_seven;
			break;
		case '8':
			digit_tiles = number_tmp::number_eight;
			break;
		case '9':
			digit_tiles = number_tmp::number_nine;
			break;
		default :
			LOG_ERROR("Unknown digit: ", digit);
			break;
	}

	return digit_tiles;
}
