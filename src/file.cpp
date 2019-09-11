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
#include <mutex>

#include "file.h"
#include "logging.h"

// ================================================================
// Output stream (write)
// ================================================================
void iofile::File::close_ofile() {
	if (this->ofile_is_open() == true) {
		this->ofile.close();
	}
}

void iofile::File::open_ofile() {
	// Open ofile only if write flag is true
	if (this->write_flag == true) {
		if (this->ofile_is_open() == false) {
			this->ofile.open(this->name, std::ios::ate | std::ios::app | std::ios::out);
			if ((this->ofile.rdstate() & std::ostream::failbit) != 0) {
				LOG_ERROR("Can't open file ", this->name, " for write");
			}
			LOG_INFO(logging::verb_level_e::HIGH, "[Open ofile] Opened file ", this->name, " for write.");
		}
	} else {
		LOG_ERROR("Can't open file ", this->name, " for write because write flag is set to ", std::boolalpha, this->write_flag);
	}
}


bool iofile::File::ofile_is_open() {
	return this->ofile.is_open();
}

// ================================================================
// Input stream (read)
// ================================================================
void iofile::File::close_ifile() {
	if (this->ifile_is_open() == true) {
		LOG_INFO(logging::verb_level_e::HIGH, "[Close ifile] Closing ifile ", this->name, " for write.");
		this->ifile.close();
	}
}

void iofile::File::open_ifile() {
	// Open ifile only if read flag is true
	if (this->read_flag == true) {
		if (this->ifile_is_open() == false) {
			this->ifile.open(this->name, std::ios::in);
			if ((this->ifile.rdstate() & std::istream::failbit) != 0) {
				LOG_ERROR("Can't open file ", this->name, " for read");
			}
			LOG_INFO(logging::verb_level_e::HIGH, "[Open ifile] Opened file ", this->name, " for read.");
		}
	} else {
		LOG_ERROR("Can't open file ", this->name, " for read because read flag is set to ", std::boolalpha, this->read_flag);
	}
}

bool iofile::File::ifile_is_open() {
	return this->ifile.is_open();
}

// ================================================================
// Destructors
// ================================================================
iofile::File::~File() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Destructor of file ", this->name)
	this->close_ifile();
	this->close_ofile();
}

// ================================================================
// Access flags
// ================================================================
void iofile::File::set_read_access() {
	// Set read flag is mode is read-write (RW) or read-only (RO)
	if ((this->mode == iofile::mode_e::NO_ACCESS) || (this->mode == iofile::mode_e::WO)) {
		this->read_flag = false;
	} else if ((this->mode == iofile::mode_e::RW) || (this->mode == iofile::mode_e::RO)) {
		this->read_flag = true;
	} else {
		LOG_ERROR("Can't set read access flag because unknown mode ");
	}
}

void iofile::File::set_write_access() {
	// Set write flag is mode is read-write (RW) or read-only (WO)
	if ((this->mode == iofile::mode_e::NO_ACCESS) || (this->mode == iofile::mode_e::RO)) {
		this->write_flag = false;
	} else if ((this->mode == iofile::mode_e::RW) || (this->mode == iofile::mode_e::WO)) {
		this->write_flag = true;
	} else {
		LOG_ERROR("Can't set write access flag because unknown mode ");
	}
}

void iofile::File::set_access_flags() {
	this->set_write_access();
	this->set_read_access();
}

// ================================================================
// Get functions
// ================================================================
std::string iofile::File::get_name() const {
	// Return filename
	return this->name;
}

iofile::mode_e iofile::File::get_access_mode() const {
	// Return access mode
	return this->mode;
}

std::ifstream & iofile::File::get_ifile() {
	// Return ifile pointer
	return this->ifile;
}

// ================================================================
// Set functions
// ================================================================
void iofile::File::set_name(std::string filename) {
	LOG_INFO(logging::verb_level_e::ZERO, "[Access Mode] Changing name of file ", this->name, " to " , filename, ". File ", this->name, " will be closed.");
	// Set filename
	this->name.assign(filename);
}

void iofile::File::set_access_mode(iofile::mode_e access_mode) {
	if (this->mode == access_mode) {
		// If access mode doesn't change, don't do anything
		LOG_INFO(logging::verb_level_e::ZERO, "[Access Mode] Access mode for file ", this->name, " unchnaged.");
	} else {
		// If access mode is different, close ifile and ofile and update it
		this->close_ofile();
		this->close_ifile();
		this->mode = access_mode;
		iofile::File::set_access_flags();
		LOG_INFO(logging::verb_level_e::ZERO, "[Access Flags] Access flags for file ", this->name, " are: write->", std::boolalpha, this->write_flag, " read->", std::boolalpha, this->read_flag, ".");
	}
}

// Overload << operator for mode_e
std::ostream& iofile::operator<< (std::ostream& os, const iofile::mode_e & mode) {

	switch (mode) {
		case iofile::mode_e::NO_ACCESS:
			os << "No ACCESS";
			break;
		case iofile::mode_e::RO:
			os << "Read-Only";
			break;
		case iofile::mode_e::WO:
			os << "Write-Only";
			break;
		case iofile::mode_e::RW:
			os << "Read-Write";
			break;
		default:
			os << "Unknown access mode";
			break;
	}

	return os;
}

std::ostream& iofile::operator<< (std::ostream& os, const iofile::File & file) {

	os << "FIle: name " << file.get_name() << " Access mode " << file.get_access_mode();

	return os;

}
