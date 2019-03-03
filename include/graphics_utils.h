#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H
/**
 * @copyright
 * @file graphics_utils.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Graphics utility header file
*/

#include <limits>

#include "window_obj.h"
#include "window_list.h"

using namespace std;

namespace graphics_utils {

	/**
	 * @brief Number of colours: 1 means black and white and 3 means RGB
	 *
	 */
	const static int no_colours = 3;

	/**
	 * @brief Palette
	 *
	 */
	typedef enum class palette_list {
		RED,
		BLUE,
		GREEN,
		YELLOW,
		PURPLE,
		PINK,
		BROWN,
		WHITE,
		BLACK
	} palette_e;

	template <typename pixel_type>
	pixel_type * get_pixel_colour (palette_e colour_name);

	void delete_window();

	void init_window_list();

	void delete_win_id(int& id);

	window_obj::WindowObj search_win_id(int& id );

	void win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)());

	window_list::WindowList * & get_window_ptr();
}

template <typename pixel_type>
pixel_type * graphics_utils::get_pixel_colour (palette_e colour_name) {
	
	pixel_type * colour = new pixel_type[graphics_utils::no_colours];
	int max_value_pixel_type = std::numeric_limits<pixel_type>::max;
	int min_value_pixel_type = std::numeric_limits<pixel_type>::min;

	switch (colour_name) {
		case graphics_utils::palette_e::RED:
			if (graphics_utils::no_colours == 3) {
				colour = {max_value_pixel_type, 0, 0};
			} else if (graphics_utils::no_colours == 1) {
				colour = max_value_pixel_type;
			}
			break;
	}
}

#endif // GRAPHICS_UTILS_H
