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
#include <algorithm>

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
			explicit BasicList(): head() {
				LOG_INFO(logging::verb_level_e::DEBUG, "Constructor of basic list");
			};

			/**
			 * @brief Function: BasicList(const BasicList& copy)
			 *
			 * \param copy: BasicList to copy
			 *
			 * BasicList copy constructor
			 */
			BasicList(const BasicList& copy): head(copy.head) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Copy constructor of basic list");
			};

			// Destructor
			/**
			 * @brief Function: virtual ~BasicList()
			 *
			 * Destructor of BasicList
			 */
			virtual ~BasicList();

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
			 * @brief Function: std::vector<class_element> & get_vector()
			 *
			 * \return head of BasicList
			 *
			 * Return a pointer to te head of the list 
			 */
			std::vector<class_element> & get_vector();

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

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const basic_list::BasicList & list)
	 *
	 * \param os: output stream
	 * \param list: list to print
	 *
	 * Overload << operator to print window details
	 */
	template <class class_element>
	std::ostream& operator<< (std::ostream& os, const basic_list::BasicList<class_element> & list);


}
/** @} */ // End of BasicListGroup group

template <class class_element>
basic_list::BasicList<class_element>::~BasicList() {

	std::string pretext ("Destructor");
	LOG_INFO(logging::verb_level_e::DEBUG, "Basic List Destructor");

	for(typename std::vector<class_element>::iterator element_it = this->head.begin(); element_it != this->head.end(); ++element_it) {
		// Convert iterator to index
		int index = std::distance(this->head.begin(), element_it);

		// Create an class_element that references the desired element
		class_element & element (this->head.at(index));

		// Print informations about the element to be deleted
		element.print_info(logging::verb_level_e::DEBUG, pretext);
		this->head.erase(element_it);
	}
	LOG_INFO(logging::verb_level_e::DEBUG, "Basic list destroyed");

}

template <class class_element>
void basic_list::BasicList<class_element>::remove_element(class_element & element) {

	typename std::vector<class_element>::iterator element_it = std::find(this->head.begin(), this->head.end(), element);
	if (element_it != this->head.end()) {
		this->head.erase(element_it);
	} else {
		std::string pretext ("Remove Element");
		element.print_info(logging::verb_level_e::MEDIUM, pretext);
		LOG_ERROR("Node has not been found");
	}
}

template <class class_element>
void basic_list::BasicList<class_element>::print_info(logging::verb_level_e verbosity, std::string pretext) {

	LOG_INFO(verbosity, "[",  pretext, "] Print information");
	LOG_INFO(verbosity, *this);
}

template <class class_element>
std::vector<class_element> & basic_list::BasicList<class_element>::get_vector() {
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

template <class class_element>
std::ostream& basic_list::operator<< (std::ostream& os, const basic_list::BasicList<class_element> & list) {
	
	std::vector<class_element> basic_list_vector (list.get_vector());

	for(typename std::vector<class_element>::iterator element_it = basic_list_vector.begin(); element_it != basic_list_vector.end(); ++element_it) {
		// Convert iterator to index
		int index = std::distance(basic_list_vector.begin(), element_it);

		// Create an class_element that references the desired element
		class_element & element (basic_list_vector.at(index));
		os << "Element number " << index << ": " << element << std::endl;
	}

	return os;
}

#endif // BASIC_LIST_H
