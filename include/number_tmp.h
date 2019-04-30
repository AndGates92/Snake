#ifndef NUMBER_TMP_H
#define NUMBER_TMP_H
/**
 * @copyright
 * @file number_tmp.h
 * @author Andrea Gianarda
 * @date 29th of April 2019
 * @brief Number template header
 */

#include "graphics_utils.h"
#include "logging.h"

namespace number_tmp {

	namespace {
		// Colouring
		graphics_utils::palette_e colour_false = graphics_utils::palette_e::BLACK;
		graphics_utils::palette_e colour_true = graphics_utils::palette_e::WHITE;
	}

	// Tile defines
	const static int num_tiles_width = 4;
	const static int num_tiles_height = 5;
	const static int num_tiles = num_tiles_height * num_tiles_width;
	const static int tile_width = 5;
	const static int tile_height = 5;
	const static int tile_pixels = num_tiles*tile_width*tile_height;

	const static bool number_zero[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  true,  true
	};

	const static bool number_one[num_tiles] = {
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false
	};

	const static bool number_two[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true
	};

	const static bool number_three[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	const static bool number_four[num_tiles] = {
		false, false, false, true,
		false, false, true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, false, false, true
	};

	const static bool number_five[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	const static bool number_six[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true
	};

	const static bool number_seven[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, false, true,  false,
		false, false, true,  false,
		false, true,  false, false
	};

	const static bool number_eight[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true
	};

	const static bool number_nine[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	template <typename pixel_type>
	void draw_digit(pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const char & digit);

	const bool * get_digit_tiles(const char & digit);
}

template <typename pixel_type>
void number_tmp::draw_digit(pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const char & digit) {

	LOG_INFO(logging::verb_level_e::DEBUG,"[Draw Digit] Draw digit ", digit, " starting at X ", init_x, " Y ", init_y);
//cout << "[Draw Digit] Draw digit " << digit << " starting at X " << init_x << " Y " << init_y << endl;
	const bool * digit_tiles = number_tmp::get_digit_tiles(digit);

	for (int tile_no = 0; tile_no < number_tmp::num_tiles; tile_no++) {
		const bool tile = digit_tiles[tile_no];
		int row = (int)tile_no/(int)number_tmp::num_tiles_width;
		// First tiles must go to the top of the number
		int init_row = (number_tmp::num_tiles_height-row-1)*number_tmp::tile_height;
		int column = tile_no % number_tmp::num_tiles_width;
		int init_column = column*number_tmp::tile_width;

		// Default colour to black
		graphics_utils::palette_e colour_name = graphics_utils::palette_e::BLACK;

		if (tile == false) {
			colour_name = number_tmp::colour_false;
		} else {
			colour_name = number_tmp::colour_true;
		}
		pixel_type * colour = graphics_utils::get_pixel_colour<pixel_type> (colour_name);

		for (int x_coord = 0; x_coord < number_tmp::tile_width; x_coord++) {
			int tile_column = init_column + x_coord;
			int curr_column = (init_x + tile_column);
			if (curr_column < win_width) {
				for (int y_coord = 0; y_coord < number_tmp::tile_height; y_coord++) {
					int tile_row = init_row + y_coord;
					int curr_row = (init_y + tile_row);
					if (curr_row < win_height) {
						LOG_INFO(logging::verb_level_e::DEBUG,"[Draw Digit] Draw pixel at coordinates (", curr_row, ", ", curr_column, ") -> Colour: ", colour_name);
						int abs_coord = curr_row*win_width + curr_column;

						for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
							pixels[graphics_utils::no_colours * abs_coord + colour_idx] = colour[colour_idx];
						}
					}
				}
			}
		}
	}

}

#endif // NUMBER_TMP_H
