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
#include <ctime>
#include <iomanip>
#include <sstream>

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

bool utility::str_to_bool (std::string str) {

	int value_int = utility::str_to_int(str);
	bool value = false;

	if (value_int == 0) {
		value = false;
	} else {
		value = true;
	}

	return value;
}

bool utility::file_exists (std::string filename) {

	bool exists = false;

	std::ifstream ifile(filename.c_str());
	// 0 means failure
	if (ifile) {
		ifile.close();
		exists = true;
	} else {
		exists = false;
	}

	return exists;
}

void utility::file_rename (std::string orig_file, std::string copy_file) {

	bool copy_file_found = false;
	copy_file_found = utility::file_exists(copy_file);

	std::string copy_filename(copy_file);

	while (copy_file_found == true) {
		std::string new_copy_file(copy_file);
		auto abstime = std::time(nullptr);
		auto ltime = *std::localtime(&abstime);
		std::ostringstream timestr;
		timestr << std::put_time(&ltime, "_%d_%m_%Y_%H_%M_%S");
		new_copy_file.append(timestr.str());
		copy_file_found = utility::file_exists(new_copy_file);
		copy_filename = new_copy_file;
	}

	// Safety net
	if (copy_file_found == true) {
		utility::file_delete(copy_filename);
	}

	bool orig_file_found = false;
	orig_file_found = utility::file_exists(orig_file);
	int rename_succesful = -1;

	if (orig_file_found == true) {
		rename_succesful = std::rename(orig_file.c_str(), copy_filename.c_str());
		if (rename_succesful != 0) {
			LOG_ERROR("Failed to rename ", orig_file, " as ", copy_filename);
		} else {
			LOG_INFO(logging::verb_level_e::LOW, "Rename ", orig_file, " as ", copy_filename);
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
