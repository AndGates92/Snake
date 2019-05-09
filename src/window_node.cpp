/**
 * @copyright
 * @file window_node.cpp
 * @author Andrea Gianarda
 * @date 18th February 2019
 * @brief Window node functions
 */

#include <string>
#include <iostream>
#include <fstream>

#include "logging.h"
#include "window_node.h"
#include "window_obj.h"

using namespace std;
using namespace logging;
using namespace window_obj;
using namespace window_node;

void window_node::WindowNode::destroy_node() {
	window_obj::WindowObj::destroy_obj();
}

window_node::WindowNode::~WindowNode() {
	std::string pretext ("Window Node Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

void window_node::WindowNode::print_info(logging::verb_level_e verbosity, std::string pretext) {
	window_obj::WindowObj::print_info(verbosity, pretext);
}
