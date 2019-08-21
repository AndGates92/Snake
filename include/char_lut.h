#ifndef NUMBER_TMP_H
#define NUMBER_TMP_H
/**
 * @copyright
 * @file char_lut.h
 * @author Andrea Gianarda
 * @date 29th of April 2019
 * @brief Number template header
 */

#include "colours.h"
#include "logging.h"
#include "settings.h"
#include "graphics_utils.h"

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

/** @defgroup CharLUTGroup Character LUT Doxygen Group
 *  Character LUT functions and classes
 *  @{
 */
namespace char_lut {
	namespace {
		// Colouring
		/**
		 * @brief Colour of tiles (writing)
		 *
		 */
		colours::palette_e colour_true = colours::palette_e::WHITE;
	}

	// Tile defines
	/**
	 * @brief Number of tiles on the horizontal axis
	 *
	 */
	const static int num_tiles_width = 4;
	/**
	 * @brief Number of tiles on the vertical axis
	 *
	 */
	const static int num_tiles_height = 5;
	/**
	 * @brief Total number of tiles
	 *
	 */
	const static int num_tiles = num_tiles_height * num_tiles_width;

	// Digits
	/**
	 * @brief Character 0 (zero)
	 *
	 */
	const static bool number_zero[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character 1 (one)
	 *
	 */
	const static bool number_one[num_tiles] = {
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false,
		false, false, true,  false
	};

	/**
	 * @brief Character 2 (two)
	 *
	 */
	const static bool number_two[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true
	};

	/**
	 * @brief Character 3 (three)
	 *
	 */
	const static bool number_three[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character 4 (four)
	 *
	 */
	const static bool number_four[num_tiles] = {
		false, false, false, true,
		false, false, true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, false, false, true
	};

	/**
	 * @brief Character 5 (five)
	 *
	 */
	const static bool number_five[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character 6 (six)
	 *
	 */
	const static bool number_six[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character 7 (seven)
	 *
	 */
	const static bool number_seven[num_tiles] = {
		false, true,  true,  true,
		false, false, false, true,
		false, false, true,  false,
		false, false, true,  false,
		false, true,  false, false
	};

	/**
	 * @brief Character 8 (eight)
	 *
	 */
	const static bool number_eight[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character 9 (nine)
	 *
	 */
	const static bool number_nine[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	// Alphabetical characters
	/**
	 * @brief Character C
	 *
	 */
	const static bool char_c[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  false, false,
		false, true,  false, false,
		false, true,  true,  true
	};

	/**
	 * @brief Character E
	 *
	 */
	const static bool char_e[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true
	};

	/**
	 * @brief Character O
	 *
	 */
	const static bool char_o[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  false, true,
		false, true,  true,  true
	};

	/**
	 * @brief Character R
	 *
	 */
	const static bool char_r[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, true,
		false, true,  true,  true,
		false, true,  true,  false,
		false, true,  false, true
	};

	/**
	 * @brief Character S
	 *
	 */
	const static bool char_s[num_tiles] = {
		false, true,  true,  true,
		false, true,  false, false,
		false, true,  true,  true,
		false, false, false, true,
		false, true,  true,  true
	};

	// Symbols
	/**
	 * @brief Character = (equal)
	 *
	 */
	const static bool char_eq[num_tiles] = {
		false, false, false, false,
		false, true,  true,  false,
		false, false, false, false,
		false, true,  true,  false,
		false, false, false, false
	};


	/**
	 * @brief Character : (colon)
	 *
	 */
	const static bool char_colon[num_tiles] = {
		false, false, false, false,
		false, true,  false, false,
		false, false, false, false,
		false, true,  false, false,
		false, false, false, false
	};

	/**
	 * @brief Function: void draw_char(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const char & char_print)
	 *
	 * \param win_height: height of the reshaped window
	 * \param win_width: width of the reshaped window
	 * \param pixels: pointer to pixels to draw passed by reference
	 * \param init_x: x coordinate of pixel the number starts
	 * \param init_y: y coordinate of pixel the number starts
	 * \param char_print: character to draw
	 *
	 * This function returns the pointer to the array of pixels to draw
	 */
	template <typename pixel_type>
	void draw_char(pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const char & char_print);

	/**
	 * @brief Function: const bool * get_char_tiles(const char & char_print)
	 *
	 * \param char_print: character to print
	 *
	 * \return array of tile values printing the character
	 *
	 * This function returns the array of tile values making up the character
	 */
	const bool * get_char_tiles(const char & char_print);

	/**
	 * @brief Function: void draw_string(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const string & str)
	 *
	 * \param win_height: height of the reshaped window
	 * \param win_width: width of the reshaped window
	 * \param pixels: pointer to pixels to draw passed by reference
	 * \param init_x: x coordinate of pixel the number starts
	 * \param init_y: y coordinate of pixel the number starts
	 * \param str: string to draw
	 *
	 * This function returns the pointer to the array of pixels to draw
	 */
	template <typename stat_pixel_type>
	void draw_string(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const string & str);

}
/** @} */ // End of CharLUTGroup group

template <typename pixel_type>
void char_lut::draw_char(pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const char & char_print) {

	LOG_INFO(logging::verb_level_e::DEBUG,"[Draw Char] Draw char ", char_print, " starting at X ", init_x, " Y ", init_y);
	const bool * char_tiles = char_lut::get_char_tiles(char_print);

	int tile_width = snake_settings.get_tile_width();
	int tile_height = snake_settings.get_tile_height();

	for (int tile_no = 0; tile_no < char_lut::num_tiles; tile_no++) {
		const bool tile = char_tiles[tile_no];
		int row = (int)tile_no/(int)char_lut::num_tiles_width;
		// First tiles must go to the top of the number
		int init_row = (char_lut::num_tiles_height-row-1)*tile_height;
		int column = tile_no % char_lut::num_tiles_width;
		int init_column = column*tile_width;

		// Default colour to black
		colours::palette_e colour_name = colours::palette_e::BLACK;

		if (tile == false) {
			// If tile is false, use background colour
			int win_id = 0;
			win_id = glutGetWindow();

			window_obj::WindowObj * node (graphics_utils::search_win_id(win_id));
			colour_name = node->get_colour_bg();

		} else {
			colour_name = char_lut::colour_true;
		}
		pixel_type * colour = colours::get_pixel_colour<pixel_type> (colour_name);

		for (int x_coord = 0; x_coord < tile_width; x_coord++) {
			int tile_column = init_column + x_coord;
			int curr_column = (init_x + tile_column);
			if (curr_column < win_width) {
				for (int y_coord = 0; y_coord < tile_height; y_coord++) {
					int tile_row = init_row + y_coord;
					int curr_row = (init_y + tile_row);
					if (curr_row < win_height) {
						LOG_INFO(logging::verb_level_e::DEBUG,"[Draw Char] Draw pixel at coordinates (", curr_row, ", ", curr_column, ") -> Colour: ", colour_name);
						int abs_coord = curr_row*win_width + curr_column;
						for (int colour_idx=0; colour_idx<colours::no_colours; colour_idx++) {
							pixels[colours::no_colours * abs_coord + colour_idx] = colour[colour_idx];
						}
					}
				}
			}
		}
	}
}

template <typename stat_pixel_type>
void char_lut::draw_string(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const string & str) {

	int tile_width = snake_settings.get_tile_width();
	//int tile_height = snake_settings.get_tile_height();

	for (unsigned pos=0; pos < str.length(); pos++) {
		char char_print = str.at(pos);
		int x_start = init_x + pos*(char_lut::num_tiles_width*tile_width);
		int y_start = init_y;
		char_lut::draw_char<stat_pixel_type>(pixels, win_width, win_height, x_start, y_start, char_print);
	}

}

#endif // NUMBER_TMP_H
