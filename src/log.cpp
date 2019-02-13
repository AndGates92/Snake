/**
 * @copyright
 * @file log.cpp
 * @author Andrea Gianarda
 * @date 04th February 2019
 * @brief Log function
 */

#include <iostream>

#include "log.h"
#include "file.h"

using namespace log;
using namespace iofile;

void log::logfileobj::close () {
	log::logfileobj::logstream.close_ofile();
	log::logfileobj::logstream.close_ifile();
}

// ================================================================
// Destructor
// ================================================================
log::logfileobj::~logfileobj() {
	log::logfileobj::close();
}
