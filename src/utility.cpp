/**
 * @copyright
 * @file utility.cpp
 * @author Andrea Gianarda
 * @date 22nd May 2019
 * @brief Utility function
 */

#include <iostream>
#include <cmath>

#include "utility.h"

using namespace std;
using namespace utility;

int utility::str_to_int (std::string str) {

	int value = 0;
	float base = 10.0;
	std::string::size_type no_digit = str.length();

	for (std::string::size_type char_no=0; char_no < no_digit; char_no++) {
		int digit = str.at(char_no) - '0';
		// -1 because the number of digit must start at 0 to count
		value += digit * ((int) pow(base, (no_digit - char_no - 1)));
	}

	return value;
}
