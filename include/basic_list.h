#ifndef BASIC_LIST_H
#define BASIC_LIST_H
/**
 * @copyright
 * @file basic_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic List header file
*/

#include <vector>

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
	template <class class_element>
	class BasicList {
		public:
			// Constructor
			/**
			 * @brief Function: BasicList()
			 *
			 * BasicList constructor
			 */
			BasicList(): head() { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

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
			 * @brief Function: void remove_element(class_element & element)
			 *
			 * \param element: element to delete
			 *
			 * Delete element
			 */
			void remove_element(class_element & element);

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
			 * @brief Function: std::vector<class_element> & get_head()
			 *
			 * \return head of BasicList
			 *
			 * Return a pointer to te head of the list 
			 */
			std::vector<class_element> & get_head();

			/**
			 * @brief Function: void set_head(std::vector<class_element> & new_head)
			 *
			 * \param new_head: set head of BasicList
			 *
			 * Set the head pointer of the list
			 */
			void set_head(std::vector<class_element> & new_head);

			/**
			 * @brief Function: void add_element()
			 *
			 * Function to add a element. It must be implemented in the derived class
			 */
			void add_element();

		protected:

		private:
			/**
			 * @brief Head of the list
			 *
			 */
			std::vector<class_element> head;

	};
}
/** @} */ // End of BasicListGroup group

template <class class_element>
basic_list::BasicList<class_element>::~BasicList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	for(typename std::vector<class_element>::iterator element_it = this->head.begin(); element_it != this->head.end(); ++element_it) {
		// Convert iterator to index
		int index = std::distance(this->head.begin(), element_it);

		// Create an class_element that references the desired element
		class_element & element (this->head.at(index));

		// Print informations about the element to be deleted
		element.print_info(logging::verb_level_e::HIGH, pretext);
		this->head.erase(element_it);
	}
	LOG_INFO(logging::verb_level_e::HIGH, "Basic list destroyed");

}

template <class class_element>
void basic_list::BasicList<class_element>::remove_element(class_element & element) {

	typename std::vector<class_element>::iterator element_it = std::find(this->head.begin(), this->head.end(), element);
	if (element_it != this->head.end()) {
		this->head.erase(element_it);
	} else {
		LOG_ERROR("Node ", element, " has not been found");
	}
}

template <class class_element>
void basic_list::BasicList<class_element>::print_info(logging::verb_level_e verbosity, std::string pretext) {

	for(auto && element : this->head) {
		element.print_info(verbosity, pretext);
	}
}

template <class class_element>
std::vector<class_element> & basic_list::BasicList<class_element>::get_head() {
	return this->head;
}

template <class class_element>
void basic_list::BasicList<class_element>::set_head(std::vector<class_element> & new_head) {
	this->head = new_head;
}

template <class class_element>
void basic_list::BasicList<class_element>::add_element() {
	LOG_ERROR("add_element function was not implemented in BasicList class. Please code it up in the derived class");
}

#endif // BASIC_LIST_H
