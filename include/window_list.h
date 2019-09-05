#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file window_list.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window List header file
*/

#include "window_obj.h"
#include "basic_obj_list.h"

/** @defgroup WindowListGroup Window List Doxygen Group
 *  Window List functions and classes
 *  @{
 */
namespace window_list {
	/**
	 * @brief WindowList class
	 *
	 */
	class WindowList : public basic_obj_list::BasicObjList<window_obj::WindowObj> {
		public:
			// Constructor
			/**
			 * @brief Function: WindowList(std::string name_win = "Window")
			 *
			 * \param name_win: name of the WindowList
			 *
			 * WindowList constructor
			 */
			explicit WindowList(std::string name_win = "Window"): basic_obj_list::BasicObjList<window_obj::WindowObj>(name_win) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: WindowList(const WindowList& copy)
			 *
			 * \param copy: WindowList to copy
			 *
			 * WindowList copy constructor
			 */
			WindowList(const WindowList& copy): basic_obj_list::BasicObjList<window_obj::WindowObj>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~WindowList()
			 *
			 * Destructor of WindowList
			 */
			~WindowList();

			/**
			 * @brief Function: int add_element(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour)
			 *
			 * \param window_title: title of the window
			 * \param window_type: type/group the window belongs to
			 * \param window_width: width of the window
			 * \param window_height: height of the window
			 * \param window_x_pos: position on the x coordinate of the window on the screen
			 * \param window_y_pos: position on the y coordinate of the window on the screen
			 * \param background_colour: background colour of the window
			 *
			 * \return window ID
			 *
			 * Add a element to WindowList
			 */
			int add_element(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour);

			/**
			 * @brief Function: window_obj::WindowObj search_by_win_id(int win_id)
			 *
			 * \param win_id: Window ID to search for
			 *
			 * \return WindowObj matching the window ID win_id
			 *
			 * Find WindowObj matching ID win_id
			 */
			window_obj::WindowObj search_by_win_id(int win_id);

			/**
			 * @brief Function: void delete_by_win_id(int win_id)
			 *
			 * \param win_id: Window ID to delete
			 *
			 * Delete WindowObj matching ID win_id
			 */
			void delete_by_win_id(int win_id);

		protected:

			/**
			 * @brief Function: void delete_element(window_obj::WindowObj * & element)
			 *
			 * \param element: WindowObj to delete
			 *
			 * Delete WindowObj element
			 */
			void delete_element(window_obj::WindowObj & element);

		private:
	};
}
/** @} */ // End of WindowListGroup group

#endif // WINDOW_LIST_H
