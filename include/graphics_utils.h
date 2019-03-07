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
	typedef enum class palette_type {
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

	std::ostream& operator<< (std::ostream& os, graphics_utils::palette_e palette);

	/**
	 * @brief Colour Index
	 *
	 */
	typedef enum class colour_idx_type {
		RED,
		GREEN,
		BLUE
	} colour_idx_e;

	template <typename pixel_type>
	pixel_type * get_pixel_colour (palette_e colour_name);

	void delete_window();

	void init_window_list();

	void delete_win_id(int& id);

	window_node::WindowNode * search_win_id(int& id );

	void win_node_add(std::string window_title, int window_width, int window_height, int window_x_pos, int window_y_pos, void (*EntryFunc)(int), void (*ItemsFunc)(), void (*WrapperFunc)());

	window_list::WindowList * & get_window_ptr();
}

template <typename pixel_type>
pixel_type * graphics_utils::get_pixel_colour (graphics_utils::palette_e colour_name) {

	ASSERT((graphics_utils::no_colours == 3) || (graphics_utils::no_colours == 1));
	pixel_type * colour = new pixel_type[graphics_utils::no_colours];
	static pixel_type max_value_pixel_type = std::numeric_limits<pixel_type>::max();
	static pixel_type min_value_pixel_type = std::numeric_limits<pixel_type>::min();

	static unsigned char max_value_uchar = std::numeric_limits<unsigned char>::max();
	static unsigned char min_value_uchar = std::numeric_limits<unsigned char>::min();

	switch (colour_name) {
		case graphics_utils::palette_e::RED:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::BLUE:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  max_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::GREEN:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::YELLOW:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::PURPLE:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  (pixel_type) (((128 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  (pixel_type) (((128 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::PINK:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  (pixel_type) (((192 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  (pixel_type) (((203 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::BROWN:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  (pixel_type) (((165 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  (pixel_type) (((42 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  (pixel_type) (((42 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::WHITE:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  max_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case graphics_utils::palette_e::BLACK:
			if (graphics_utils::no_colours == 3) {
				colour[(int)graphics_utils::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)graphics_utils::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (graphics_utils::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		default:
			LOG_ERROR("Invalid colour chosen: ", colour_name);
			break;
	}

	return colour;
}

#endif // GRAPHICS_UTILS_H
