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
	if (this->ofile.is_open() == true) {
		LOG_INFO(log::verb_level_e::MEDIUM, "[Close file] Closing ofile ", this->name);
		this->ofile.close();
	}
}



void iofile::File::open_ofile() {
	if (this->write_flag == true) {
		if (this->ofile.is_open() == false) {
			this->ofile.open(this->name, std::ios::ate | std::ios::app | std::ios::out);
			if ((this->ofile.rdstate() & std::ostream::failbit) != 0) {
				log::log_error("Can't open file ", this->name, " for write");
			}
			LOG_INFO(log::verb_level_e::MEDIUM, "[LOG INFO] Opened file ", this->name, " for write.");
		}
	} else {
		log::log_error("Can't open file ", this->name, " for write because write flag is set to ", std::boolalpha, this->write_flag);
	}
}


bool iofile::File::ofile_is_open() {
	return this->ofile.is_open();
}

// ================================================================
// Input stream (read)
// ================================================================
void iofile::File::open_ifile() {
	if (this->read_flag == true) {
		if (this->ifile.is_open() == false) {
			this->ifile.open(this->name, std::ios::in);
			if ((this->ifile.rdstate() & std::istream::failbit) != 0) {
				log::log_error("Can't open file ", this->name, " for read");
			}
			LOG_INFO(log::verb_level_e::MEDIUM, "[LOG INFO] Opened file ", "dada", " for read.");
		}
	} else {
		log::log_error("Can't open file ", this->name, " for read because read flag is set to ", std::boolalpha, this->read_flag);
	}
}

void iofile::File::close_ifile() {
	LOG_INFO(log::verb_level_e::MEDIUM, "[Close file] Closing file ", this->name);
	if (this->ifile.is_open() == true) {
		this->ifile.close();
	}
}

bool iofile::File::ifile_is_open() {
	return this->ifile.is_open();
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
	if ((this->mode == iofile::mode_e::NO_ACCESS) || (this->mode == iofile::mode_e::WO)) {
		this->read_flag = false;
	} else if ((this->mode == iofile::mode_e::RW) || (this->mode == iofile::mode_e::RO)) {
		this->read_flag = true;
	} else {
		log::log_error("Can't set read access flag because unknown mode ");
	}
}

void iofile::File::set_write_access() {
	if ((this->mode == iofile::mode_e::NO_ACCESS) || (this->mode == iofile::mode_e::RO)) {
		this->write_flag = false;
	} else if ((this->mode == iofile::mode_e::RW) || (this->mode == iofile::mode_e::WO)) {
		this->write_flag = true;
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
	return this->name;
}

iofile::mode_e iofile::File::get_access_mode() {
	return this->mode;
}

// ================================================================
// Set functions
// ================================================================
void iofile::File::set_filename(std::string filename) {
	LOG_INFO(log::verb_level_e::ZERO, "[Access Mode] Changing name of file ", this->name, " to " , filename, ". File ", this->name, " will be closed.");
	this->name.assign(filename);
}

void iofile::File::set_access_mode(iofile::mode_e access_mode) {
	if (this->mode == access_mode) {
		LOG_INFO(log::verb_level_e::ZERO, "[Access Mode] Access mode for file ", this->name, " unchnaged.");
	} else {
		iofile::File::close_ofile();
		iofile::File::close_ifile();
		this->mode = access_mode;
		iofile::File::set_access_flags();
	}
}


