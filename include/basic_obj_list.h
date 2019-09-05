#ifndef BASIC_OBJ_LIST_H
#define BASIC_OBJ_LIST_H
/**
 * @copyright
 * @file basic_obj_list.h
 * @author Andrea Gianarda
 * @date 26th March 2019
 * @brief Basic Object List header file
*/

#include "basic_list.h"

/** @defgroup BasicObjListGroup Basic Object List Doxygen Group
 *  Basic Object List functions and classes
 *  @{
 */
namespace basic_obj_list {
	/**
	 * @brief BasicObjList class
	 *
	 */
	template <class class_element>
	class BasicObjList : public basic_list::BasicList<class_element> {
		public:
			// Constructor
			/**
			 * @brief Function: BasicObjList(std::string name_obj = "Unknown")
			 *
			 * \param name_obj: Name of the object
			 *
			 * BasicObjList constructor
			 */
			explicit BasicObjList(std::string name_obj = "Unknown"): basic_list::BasicList<class_element>(), name(name_obj) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: BasicObjList(const BasicObjList& copy)
			 *
			 * \param copy: BasicObjList to copy
			 *
			 * BasicObjList copy constructor
			 */
			BasicObjList(const BasicObjList& copy): basic_list::BasicList<class_element>(copy), name(copy.name) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: virtual ~BasicObjList()
			 *
			 * Destructor of BasicObjList
			 */
			virtual ~BasicObjList();

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
			 * @brief Name of the object list
			 *
			 */
			std::string name;
	};
}
/** @} */ // End of BasicObjListGroup group

template <class class_element>
basic_obj_list::BasicObjList<class_element>::~BasicObjList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	LOG_INFO(logging::verb_level_e::HIGH, "Basic Object List destroyed");

}

template <class class_element>
std::string basic_obj_list::BasicObjList<class_element>::get_name() {
	return this->name;
}

template <class class_element>
void basic_obj_list::BasicObjList<class_element>::set_name(std::string new_name) {
	this->name = new_name;
}

template <class class_element> template <typename pixel_type>
void basic_obj_list::BasicObjList<class_element>::draw(pixel_type * & pixels, const int & win_width, const int & win_height, const int & exp_no) {
	std::vector<class_element> & basic_obj = this->get_vector();

	int obj_cnt = 0;

	for (auto obj : basic_obj) {

		obj.draw(pixels, win_width, win_height);

		obj_cnt++;

	}

	ASSERT(exp_no == obj_cnt);

}
#endif // BASIC_OBJ_LIST_H
