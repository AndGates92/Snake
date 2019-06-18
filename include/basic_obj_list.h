#ifndef BASIC_OBJ_LIST_H
#define BASIC_OBJ_LIST_H
/**
 * @copyright
 * @file basic_obj_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic Object List header file
*/

/** @defgroup BasicObjListGroup Basic Object List Doxygen Group
 *  Basic Object List functions and classes
 *  @{
 */
namespace basic_obj_list {
	template <class class_node>
	class BasicObjList {
		public:
			// Constructor
			/**
			 * @brief Function: BasicObjList(std::string name_obj = "Unknown")
			 *
			 * \param name_obj: Name of the object
			 *
			 * BasicObjList constructor
			 */
			BasicObjList(std::string name_obj = "Unknown"): head(nullptr), name(name_obj) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: BasicObjList(const BasicObjList& copy)
			 *
			 * \param copy: BasicObjList to copy
			 *
			 * BasicObjList copy constructor
			 */
			BasicObjList(const BasicObjList& copy): head(copy.head), name(copy.name) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~BasicObjList()
			 *
			 * Destructor of BasicObjList
			 */
			~BasicObjList();

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
			 * \param pretext: text to prepend to the BasicObjList information
			 *
			 * Print BasicObjList information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: class_node * & get_head()
			 *
			 * \return head of BasicObjList
			 *
			 * Return a pointer to te head of the object list 
			 */
			class_node * & get_head();

			/**
			 * @brief Function: void set_head(class_node * & new_head)
			 *
			 * \param new_head: set head of BasicObjList
			 *
			 * Set the head pointer of the object list
			 */
			void set_head(class_node * & new_head);

			/**
			 * @brief Function: std::string get_name()
			 *
			 * \return name of the BasicObjList instance
			 *
			 * Return the name of the object list
			 */
			std::string get_name();

			/**
			 * @brief Function: void set_name(std::string new_name)
			 *
			 * \param new_name: name of the BasicObjList instance
			 *
			 * Change name of the object list
			 */
			void set_name(std::string new_name);

			/**
			 * @brief Function: void draw(pixel_type * & pixels, const int & win_width, const int & win_height, const int & exp_no)
			 *
			 * \param pixels: pixels in the window
			 * \param win_width: width of the window
			 * \param win_height: height of the window
			 * \param exp_no: expected number of elements
			 *
			 * Draw the object list elements
			 */
			template <typename pixel_type>
			void draw(pixel_type * & pixels, const int & win_width, const int & win_height, const int & exp_no);

		protected:

		private:
			/**
			 * @brief Head of the list
			 *
			 */
			class_node * head;
			/**
			 * @brief Name of the object list
			 *
			 */
			std::string name;
	};
}
/** @} */ // End of BasicObjListGroup group

template <class class_node>
basic_obj_list::BasicObjList<class_node>::~BasicObjList() {

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
	LOG_INFO(logging::verb_level_e::HIGH, "Basic Object list destroyed");

}

template <class class_node>
void basic_obj_list::BasicObjList<class_node>::remove_node(class_node * & node) {
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
	node->print_info(logging::verb_level_e::LOW, pretext);
	delete node;
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
void basic_obj_list::BasicObjList<class_node>::set_name(std::string new_name) {
	this->name = new_name;
}

template <class class_node> template <typename pixel_type>
void basic_obj_list::BasicObjList<class_node>::draw(pixel_type * & pixels, const int & win_width, const int & win_height, const int & exp_no) {
	class_node * basic_obj = this->head;

	int obj_cnt = 0;

	while (basic_obj != nullptr) {

		basic_obj->draw(pixels, win_width, win_height);
		basic_obj = basic_obj->get_next();

		obj_cnt++;

	}

	ASSERT(exp_no == obj_cnt);

}
#endif // BASIC_OBJ_LIST_H
