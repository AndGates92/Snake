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

	void delete_window();

	void delete_all_windows();

	void init_window_list();

	void delete_win_id(int& id);

	window_node::WindowNode * search_win_id(int& id );

	int win_node_add(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour);

	void refresh_window(int value);

	window_list::WindowList * & get_window_ptr();

	void save_window(iofile::File & savefile);

}


#endif // GRAPHICS_UTILS_H
