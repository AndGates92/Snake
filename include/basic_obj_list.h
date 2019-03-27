#ifndef BASIC_OBJ_LIST_H
#define BASIC_OBJ_LIST_H
/**
 * @copyright
 * @file basic_obj_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic Object List header file
*/

#include "graphics_utils.h"

namespace basic_obj_list {
	/** @defgroup BasicObjListGroup Basic Object List Doxygen Group
	 *  Basic Object List functions and classes
	 *  @{
	 */

	template <class class_node>
	class BasicObjList {
		public:
			// Constructor
			BasicObjList(std::string name_obj = "Unknown"): head(nullptr), name(name_obj) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			BasicObjList(const BasicObjList& copy): head(copy.head), name(copy.name) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~BasicObjList();

			void add_node(int centre_x, int centre_y, int basic_obj_width, int basic_obj_height, graphics_utils::palette_e basic_obj_colour);
			void remove_node(class_node * & node);

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
	/** @} */ // End of BasicObjListGroup group
}

template <class class_node>
basic_obj_list::BasicObjList<class_node>::~BasicObjList() {

	std::string pretext ("BasicObj List Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	class_node * node_ptr = this->head;
	while (this->head != nullptr) {
		node_ptr = this->head;
		node_ptr->print_info(logging::verb_level_e::LOW, pretext);
		this->head = this->head->get_next();
		node_ptr->~class_node();
	}
	LOG_INFO(logging::verb_level_e::HIGH, "BasicObj list destroyed");

}

template <class class_node>
void basic_obj_list::BasicObjList<class_node>::remove_node(class_node * & node) {
	class_node * node_saved = node;

	if (node == this->head) {
		// Move head pointer as basic_obj list to delete is the head
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
	node_saved->print_info(logging::verb_level_e::LOW, pretext);

//	delete [] node;
}

template <class class_node>
void basic_obj_list::BasicObjList<class_node>::print_info(logging::verb_level_e verbosity, std::string pretext) {
	class_node * basic_obj = this->head;

	while (basic_obj != nullptr) {
		basic_obj->print_info(verbosity, pretext);
		basic_obj = basic_obj->get_next();
	}
}

template <class class_node>
class_node * & basic_obj_list::BasicObjList<class_node>::get_head() {
	return this->head;
}

template <class class_node>
std::string basic_obj_list::BasicObjList<class_node>::get_name() {
	return this->name;
}

template <class class_node>
void basic_obj_list::BasicObjList<class_node>::set_head(class_node * & new_head) {
	this->head = new_head;
}

template <class class_node>
void  basic_obj_list::BasicObjList<class_node>::set_name(std::string new_name) {
	this->name = new_name;
}
#endif // BASIC_OBJ_LIST_H
