#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H
/**
 * @copyright
 * @file graphics_utils.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Graphics utility header file
*/

#include <iostream>

#include "window_list.h"

using namespace std;

/** @defgroup GraphicsUtilsGroup Graphics Utils Doxygen Group
 *  Graphic utility functions and classes
 *  @{
 */
namespace graphics_utils {

	namespace {

		/**
		 * @brief FIeld of view
		 *
		 */
		const static GLfloat zoom = 50.0;

		/**
		 * @brief Near clip
		 *
		 */
		const static GLfloat zNear = 1.0;

		/**
		 * @brief Far clip
		 *
		 */
		const static GLfloat zFar = 1.0;

		/**
		 * @brief Far clip
		 *
		 */
		const static int refresh_timer_ms = 20;

	}

	/**
	 * @brief Function: void delete_window()
	 *
	 * Delete current window
	 */
	void delete_window();

	/**
	 * @brief Function: void delete_all_window()
	 *
	 * Delete all windows
	 */
	void delete_all_windows();

	/**
	 * @brief Function: void init_window_list()
	 *
	 * Initialize window list
	 */
	void init_window_list();

	/**
	 * @brief Function: void delete_win_id(int & id)
	 *
	 * \param id: ID of the window to delete
	 *
	 * Delete window with ID provided as input 
	 */
	void delete_win_id(int & id);

	/**
	 * @brief Function: window_obj::WindowObj * search_win_id(int & id)
	 *
	 * \param id: ID of the window to search
	 *
	 * \return window node matching ID provided as input
	 *
	 * Search window with ID provided as input
	 */
	window_obj::WindowObj * search_win_id(int & id);

	/**
	 * @brief Function: int win_node_add(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour)
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
	 * Add a node to WindowList instance
	 */
	int win_node_add(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour);

	/**
	 * @brief Function: void refresh_window(int value)
	 *
	 * \param value: timer value to trigger a refresh of the window
	 *
	 * Enable constant refresh of window based on a timer
	 */
	void refresh_window(int value);

	/**
	 * @brief Function: window_list::WindowList * & get_window_ptr()
	 *
	 * \return pointer towards WindowList instance
	 *
	 * Get pointer to WindowList instance
	 */
	window_list::WindowList * & get_window_ptr();

	/**
	 * @brief Function: void save_window(iofile::File & savefile)
	 *
	 * \param savefile: file where the save the status
	 *
	 * Save status of the game
	 */
	void save_window(iofile::File & savefile);

}
/** @} */ // End of GraphicsUtilsGroup group

#endif // GRAPHICS_UTILS_H
