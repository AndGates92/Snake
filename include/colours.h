#ifndef COLOURS_H
#define COLOURS_H
/**
 * @copyright
 * @file colours.h
 * @author Andrea Gianarda
 * @date 2nd of May 2019
 * @brief Colours header file
*/

#include <limits>

#include "logging.h"

using namespace std;

namespace colours {

	namespace {
		/**
		 * @brief Number of colours: 1 means black and white and 3 means RGB
		 *
		 */
		const static int no_colours = 3;
	}

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
		BLACK,
		UNKNOWN
	} palette_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, colours::palette_e palette)
	 *
	 * \param os: output stream
	 * \param palette: colour in the palette to print
	 *
	 * Overload << operator to print access mode 
	 */
	std::ostream& operator<< (std::ostream& os, colours::palette_e palette);

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

}


template <typename pixel_type>
pixel_type * colours::get_pixel_colour (colours::palette_e colour_name) {

	ASSERT((colours::no_colours == 3) || (colours::no_colours == 1));
	pixel_type * colour = new pixel_type[colours::no_colours];
	if (colour == nullptr) {
		LOG_ERROR("Can't allocate memory for colour array");
	}

	static pixel_type max_value_pixel_type = std::numeric_limits<pixel_type>::max();
	static pixel_type min_value_pixel_type = std::numeric_limits<pixel_type>::min();

	static unsigned char max_value_uchar = std::numeric_limits<unsigned char>::max();
	static unsigned char min_value_uchar = std::numeric_limits<unsigned char>::min();

	switch (colour_name) {
		case colours::palette_e::RED:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::BLUE:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  max_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::GREEN:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::YELLOW:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::PURPLE:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  (pixel_type) (((128 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)colours::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  (pixel_type) (((128 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::PINK:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  (pixel_type) (((192 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)colours::colour_idx_e::BLUE] =  (pixel_type) (((203 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::BROWN:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  (pixel_type) (((165 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)colours::colour_idx_e::GREEN] =  (pixel_type) (((42 / ((float)max_value_uchar- (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
				colour[(int)colours::colour_idx_e::BLUE] =  (pixel_type) (((42 / ((float)max_value_uchar - (float)min_value_uchar)) * (float)max_value_pixel_type) + (float)min_value_pixel_type);
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::WHITE:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  max_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  max_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		case colours::palette_e::BLACK:
			if (colours::no_colours == 3) {
				colour[(int)colours::colour_idx_e::RED] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::GREEN] =  min_value_pixel_type;
				colour[(int)colours::colour_idx_e::BLUE] =  min_value_pixel_type;
			} else if (colours::no_colours == 1) {
				colour[0] =  max_value_pixel_type;
			}
			break;
		default:
			LOG_ERROR("Invalid colour chosen: ", colour_name);
			break;
	}

	return colour;
}

#endif // COLOURS_H
