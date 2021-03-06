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
			explicit BasicList(): element_vector() {
				LOG_INFO(logging::verb_level_e::DEBUG, "Constructor of basic list");
			};

			/**
			 * @brief Function: BasicList(const BasicList& copy)
			 *
			 * \param copy: BasicList to copy
			 *
			 * BasicList copy constructor
			 */
			BasicList(const BasicList& copy): element_vector(copy.element_vector) {
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
			 * @brief Function: void delete_all_elements()
			 *
			 * Remove all elements from BasicList
			 */
			void delete_all_elements();

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
			 * @brief Function: std::vector<class_element> get_vector() const
			 *
			 * \return vector of BasicList
			 *
			 * Return a pointer to te vector of the list 
			 */
			std::vector<class_element> get_vector() const;

			/**
			 * @brief Function: std::vector<class_element> & get_vector()
			 *
			 * \return vector of BasicList
			 *
			 * Return a pointer to te vector of the list 
			 */
			std::vector<class_element> & get_vector();

			/**
			 * @brief Function: void set_vector(std::vector<class_element> & new_vector)
			 *
			 * \param new_vector: set vector of BasicList
			 *
			 * Set the vector pointer of the list
			 */
			void set_vector(std::vector<class_element> & new_vector);

		protected:

		private:
			/**
			 * @brief Head of the list
			 *
			 */
			std::vector<class_element> element_vector;

	};

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const basic_list::BasicList & list)
	 *
	 * \param os: output stream
	 * \param list: list to print
	 *
	 * Overload << operator to print basic list details
	 */
	template <class class_element>
	std::ostream& operator<< (std::ostream& os, const basic_list::BasicList<class_element> & list);


}
/** @} */ // End of BasicListGroup group

template <class class_element>
basic_list::BasicList<class_element>::~BasicList() {

	LOG_INFO(logging::verb_level_e::DEBUG, "Basic List Destructor");

}

 template <class class_element>
void  basic_list::BasicList<class_element>::delete_all_elements() {
 
	std::string pretext ("Delete Elements");
	this->print_info(logging::verb_level_e::LOW, pretext);

	// Delete all elements of previous vector by assigning an empty one
	this->element_vector = std::vector<class_element>();
	LOG_INFO(logging::verb_level_e::DEBUG, "Basic list cleared");

}

template <class class_element>
void basic_list::BasicList<class_element>::remove_element(class_element & element) {

	typename std::vector<class_element>::iterator element_it(std::find(this->element_vector.begin(), this->element_vector.end(), element));
	if (element_it != this->element_vector.end()) {
		this->element_vector.erase(element_it);
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
std::vector<class_element> basic_list::BasicList<class_element>::get_vector() const {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Get Vector] Get const vector");
	return this->element_vector;
}

template <class class_element>
std::vector<class_element> & basic_list::BasicList<class_element>::get_vector() {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Get Vector] Get reference to vector");
	return this->element_vector;
}

template <class class_element>
void basic_list::BasicList<class_element>::set_vector(std::vector<class_element> & new_vector) {
	this->element_vector = new_vector;
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
