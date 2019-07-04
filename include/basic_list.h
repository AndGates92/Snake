#ifndef BASIC_LIST_H
#define BASIC_LIST_H
/**
 * @copyright
 * @file basic_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic List header file
*/

#include "logging.h"

/** @defgroup BasicListGroup Basic List Doxygen Group
 *  Basic List functions and classes
 *  @{
 */
namespace basic_list {

	/**
	 * @brief BasicList class
	 *
	 */
	template <class class_node>
	class BasicList {
		public:
			// Constructor
			/**
			 * @brief Function: BasicList()
			 *
			 * BasicList constructor
			 */
			BasicList(): head(nullptr) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: BasicList(const BasicList& copy)
			 *
			 * \param copy: BasicList to copy
			 *
			 * BasicList copy constructor
			 */
			BasicList(const BasicList& copy): head(copy.head) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~BasicList()
			 *
			 * Destructor of BasicList
			 */
			~BasicList();

			/**
			 * @brief Function: void remove_node(class_node * & node)
			 *
			 * \param node: node to delete
			 *
			 * Delete node
			 */
			void remove_node(class_node * & node);

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the BasicList information
			 *
			 * Print BasicList information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: class_node * & get_head()
			 *
			 * \return head of BasicList
			 *
			 * Return a pointer to te head of the list 
			 */
			class_node * & get_head();

			/**
			 * @brief Function: void set_head(class_node * & new_head)
			 *
			 * \param new_head: set head of BasicList
			 *
			 * Set the head pointer of the list
			 */
			void set_head(class_node * & new_head);

			/**
			 * @brief Function: void add_node()
			 *
			 * Function to add a node. It must be implemented in the derived class
			 */
			void add_node();

		protected:

		private:
			/**
			 * @brief Head of the list
			 *
			 */
			class_node * head;

	};
}
/** @} */ // End of BasicListGroup group

template <class class_node>
basic_list::BasicList<class_node>::~BasicList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	class_node * node_ptr = this->head;
	while (this->head != nullptr) {
		node_ptr = this->head;
		node_ptr->print_info(logging::verb_level_e::LOW, pretext);
		this->head = this->head->get_next();
		node_ptr->~class_node();
		delete node_ptr;
	}
	LOG_INFO(logging::verb_level_e::HIGH, "Basic list destroyed");

}

template <class class_node>
void basic_list::BasicList<class_node>::remove_node(class_node * & node) {
	if (node == this->head) {
		// Move head pointer as basic_list list to delete is the head
		if (node->get_next() == nullptr) {
			this->head = nullptr;
		} else {
			this->head = this->head->get_next();
			this->head->get_prev() = nullptr;
		}
	} else {
		if (node->get_prev() != nullptr) {
			node->get_prev()->get_next() = node->get_next();
		}
		if (node->get_next() != nullptr) {
			node->get_next()->get_prev() = node->get_prev();
		}
	}

	std::string pretext ("Destructor");
	node->print_info(logging::verb_level_e::LOW, pretext);
	delete node;
}

template <class class_node>
void basic_list::BasicList<class_node>::print_info(logging::verb_level_e verbosity, std::string pretext) {
	class_node * node_ptr = this->head;

	while (node_ptr != nullptr) {
		node_ptr->print_info(verbosity, pretext);
		node_ptr = node_ptr->get_next();
	}
}

template <class class_node>
class_node * & basic_list::BasicList<class_node>::get_head() {
	return this->head;
}

template <class class_node>
void basic_list::BasicList<class_node>::set_head(class_node * & new_head) {
	this->head = new_head;
}

template <class class_node>
void basic_list::BasicList<class_node>::add_node() {
	LOG_ERROR("add_node function was not implemented in BasicList class. Please code it up in the derived class");
}

#endif // BASIC_LIST_H
