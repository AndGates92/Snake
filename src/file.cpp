/**
 * @copyright
 * @file file.cpp
 * @author Andrea Gianarda
 * @date 06th February 2019
 * @brief File function
 */

#include <string>
#include <iostream>
#include <fstream>

#include "file.h"
#include "log.h"

using namespace std;
using namespace iofile;
using namespace log;

// ================================================================
// Output stream (write)
// ================================================================
void iofile::File::close_ofile() {
	if (ofile.is_open() == true) {
		LOG_INFO(log::verb_level_e::MEDIUM, "[Close file] Closing ofile ", name);
		ofile.close();
	}
}



void iofile::File::open_ofile() {
	if (write_flag == true) {
		if (ofile.is_open() == false) {
			ofile.open(name, std::ios::ate | std::ios::app | std::ios::out);
			if ((ofile.rdstate() & std::ostream::failbit) != 0) {
				log::log_error("Can't open file ", name, " for write");
			}
			LOG_INFO(log::verb_level_e::MEDIUM, "[LOG INFO] Opened file ", name, " for write.");
		}
	} else {
		log::log_error("Can't open file ", name, " for write because write flag is set to ", std::boolalpha, write_flag);
	}
}


bool iofile::File::ofile_is_open() {
	return ofile.is_open();
}

// ================================================================
// Input stream (read)
// ================================================================
void iofile::File::open_ifile() {
	if (read_flag == true) {
		if (ifile.is_open() == false) {
			ifile.open(name, std::ios::in);
			if ((ifile.rdstate() & std::istream::failbit) != 0) {
				log::log_error("Can't open file ", name, " for read");
			}
			LOG_INFO(log::verb_level_e::MEDIUM, "[LOG INFO] Opened file ", "dada", " for read.");
		}
	} else {
		log::log_error("Can't open file ", name, " for read because read flag is set to ", std::boolalpha, read_flag);
	}
}

void iofile::File::close_ifile() {
	LOG_INFO(log::verb_level_e::MEDIUM, "[Close file] Closing file ", name);
	if (ifile.is_open() == true) {
		ifile.close();
	}
}

bool iofile::File::ifile_is_open() {
	return ifile.is_open();
}

// ================================================================
// Destructors
// ================================================================
iofile::File::~File() {
	iofile::File::close_ofile();
	iofile::File::close_ifile();
}

// ================================================================
// Access flags
// ================================================================
void iofile::File::set_read_access() {
	if ((mode == iofile::mode_e::NO_ACCESS) || (mode == iofile::mode_e::WO)) {
		read_flag = false;
	} else if ((mode == iofile::mode_e::RW) || (mode == iofile::mode_e::RO)) {
		read_flag = true;
	} else {
		log::log_error("Can't set read access flag because unknown mode ");
	}
}

void iofile::File::set_write_access() {
	if ((mode == iofile::mode_e::NO_ACCESS) || (mode == iofile::mode_e::RO)) {
		write_flag = false;
	} else if ((mode == iofile::mode_e::RW) || (mode == iofile::mode_e::WO)) {
		write_flag = true;
	} else {
		log::log_error("Can't set write access flag because unknown mode ");
	}
}

void iofile::File::set_access_flags() {
	iofile::File::set_write_access();
	iofile::File::set_read_access();
}

// ================================================================
// Get functions
// ================================================================
std::string iofile::File::get_name() {
	return name;
}

iofile::mode_e iofile::File::get_access_mode() {
	return mode;
}

// ================================================================
// Set functions
// ================================================================
void iofile::File::set_filename(std::string filename) {
	LOG_INFO(log::verb_level_e::ZERO, "[Access Mode] Changing name of file ", name, " to " , filename, ". File ", name, " will be closed.");
	name.assign(filename);
}

void iofile::File::set_access_mode(iofile::mode_e access_mode) {
	if (mode == access_mode) {
		LOG_INFO(log::verb_level_e::ZERO, "[Access Mode] Access mode for file ", name, " unchnaged.");
	} else {
		iofile::File::close_ofile();
		iofile::File::close_ifile();
		mode = access_mode;
		iofile::File::set_access_flags();
	}
}


