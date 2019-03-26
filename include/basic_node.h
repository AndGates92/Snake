#ifndef BASIC_NODE_H
#define BASIC_NODE_H
/**
 * @copyright
 * @file basic_node.h
 * @author Andrea Gianarda
 * @date 25th March 2019
 * @brief Basic Node header file
*/

#include <iostream>

#include "basic_node.h"
#include "basic_object.h"
#include "logging.h"
#include "graphics_utils.h"

using namespace std;
using namespace logging;

namespace basic_node {
	/** @defgroup BasicNodeGroup Basic Node Doxygen Group
	 *  Basic Node functions and classes
	 *  @{
	 */

	template <class class_node>
	class BasicNode {
		public:
			// Constructor
			BasicNode(): prev(nullptr), next(nullptr) {
				std::string pretext ("Basic node Constructor");
				basic_node::BasicNode<class_node>::print_info(logging::verb_level_e::LOW, pretext);
			};

			BasicNode(const class_node& copy) : prev(copy.prev), next(copy.next) { LOG_INFO(logging::verb_level_e::LOW, "Basic Node copy contructor") };

			// Destructor
			~BasicNode();

			// Get functions
			class_node * & get_next();
			class_node * & get_prev();

			// Set functions
			void set_next(class_node * next_ptr);
			void set_prev(class_node * prev_ptr);

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			class_node * prev;
			class_node * next;
	};
	/** @} */ // End of BasicNodeGroup group
}

// ================================================================
// Obstacle Node
// ================================================================
template <class class_node>
basic_node::BasicNode<class_node>::~BasicNode() {
	std::string pretext ("Basic Node Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);
}

// ================================================================
// Get functions
// ================================================================

template <class class_node>
class_node * & basic_node::BasicNode<class_node>::get_next() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Get pointer next: ", this->next);
	return this->next;
}

template <class class_node>
class_node * & basic_node::BasicNode<class_node>::get_prev() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Get pointer prev: ", this->prev);
	return this->prev;
}

// ================================================================
// Set functions
// ================================================================

template <class class_node>
void basic_node::BasicNode<class_node>::set_next(class_node * next_ptr) {
	this->next = next_ptr;
}

template <class class_node>
void basic_node::BasicNode<class_node>::set_prev(class_node * prev_ptr) {
	this->prev = prev_ptr;
}

template <class class_node>
void basic_node::BasicNode<class_node>::print_info(logging::verb_level_e verbosity, std::string pretext) {
	LOG_INFO(verbosity, "[", pretext, "] Pointer addresses: next ", this->next, " previous " , this->prev, ".");
}
#endif // BASIC_NODE_H