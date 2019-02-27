#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H
/**
 * @copyright
 * @file graphics_utils.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Graphics utility header file
*/

#include "window_obj.h"
#include "window_list.h"

namespace graphics_utils {

	void delete_window();

	void init_window_list();

	void delete_win_id(int& id);

	window_obj::WindowObj search_win_id(int& id );

	void win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)());

	window_list::WindowList * & get_window_ptr();
}


#endif // GRAPHICS_UTILS_H
