/**
 * @copyright
 * @file utility.cpp
 * @author Andrea Gianarda
 * @date 22nd May 2019
 * @brief Utility function
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

#include "utility.h"
#include "logging.h"

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

bool utility::file_exists (std::string filename) {

	bool exists = false;

	std::ifstream ifile;
	ifile.open(filename, std::ios::in);
	// 0 means failure
	if ((ifile.rdstate() & std::istream::badbit) == 0) {
		exists = false;
	} else {
		ifile.close();
		exists = true;
	}

	return exists;
}

void utility::file_rename (std::string orig_file, std::string copy_file) {

	bool copy_file_found = false;
	copy_file_found = utility::file_exists(copy_file);

	if (copy_file_found == true) {
		utility::file_delete(copy_file);
	}

	bool orig_file_found = false;
	orig_file_found = utility::file_exists(orig_file);
	int rename_succesful = -1;

	if (orig_file_found == true) {
		rename_succesful = std::rename(orig_file.c_str(), copy_file.c_str());
		if (rename_succesful != 0) {
			LOG_ERROR("Failed to rename ", orig_file, " as ", copy_file);
		}
	} else {
		LOG_INFO(logging::verb_level_e::LOW, "[File rename] Original file ", orig_file, " doesn't exists.");
	}

}

void utility::file_delete (std::string filename) {

	bool file_found = false;
	file_found = utility::file_exists(filename);

	if (file_found == true) {
		std::remove(filename.c_str());
	}
}
