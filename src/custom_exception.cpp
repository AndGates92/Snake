/**
 * @copyright
 * @file custom_exception.cpp
 * @author Andrea Gianarda
 * @date 04th September 2019
 * @brief Custom Exception 
*/

#include <iostream>

#include "logging.h"
#include "custom_exception.h"

custom_exception::CustomException::~CustomException() throw() {
	LOG_INFO(logging::verb_level_e::LOW, "Destructor")
}

const char * custom_exception::CustomException::what() const throw() {
	return this->message.c_str();
}
