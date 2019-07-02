#ifndef BASIC_LIST_H
#define BASIC_LIST_H
/**
 * @copyright
 * @file basic_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic List header file
*/

namespace basic_list {
	/** @defgroup BasicListGroup Basic List Doxygen Group
	 *  Basic List functions and classes
	 *  @{
	 */

	template <class class_node>
	class BasicList {
		public:
			// Constructor
			/**
			 * @brief Function: BasicList(std::string name_list = "Unknown")
			 *
			 * \param name_list: Name of the list 
			 *
			 * BasicList constructor
			 */
			BasicList(std::string name_list = "Unknown"): head(nullptr), name(name_list) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: BasicList(const BasicList& copy)
			 *
			 * \param copy: BasicList to copy
			 *
			 * BasicList copy constructor
			 */
			BasicList(const BasicList& copy): head(copy.head), name(copy.name) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~BasicList()
			 *
			 * Destructor of BasicList
			 */
			~BasicList();

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

			class_node * & get_head();
			void set_head(class_node * & new_head);

			std::string get_name();
			void set_name(std::string new_name);

		protected:

		private:
			class_node * head;
			std::string name;
	};
	/** @} */ // End of BasicListGroup group
}

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
	class_node * basic_list = this->head;

	while (basic_list != nullptr) {
		basic_list->print_info(verbosity, pretext);
		basic_list = basic_list->get_next();
	}
}

template <class class_node>
class_node * & basic_list::BasicList<class_node>::get_head() {
	return this->head;
}

template <class class_node>
std::string basic_list::BasicList<class_node>::get_name() {
	return this->name;
}

template <class class_node>
void basic_list::BasicList<class_node>::set_head(class_node * & new_head) {
	this->head = new_head;
}

template <class class_node>
void basic_list::BasicList<class_node>::set_name(std::string new_name) {
	this->name = new_name;
}
#endif // BASIC_LIST_H
