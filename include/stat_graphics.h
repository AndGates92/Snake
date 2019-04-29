#ifndef STAT_GRAPHICS_H
#define STAT_GRAPHICS_H
/**
 * @copyright
 * @file stat_graphics.h
 * @author Andrea Gianarda
 * @date 25th of April 2019
 * @brief Stat graphics header file
*/

#include "number_tmp.h"
#include "graphics_utils.h"

using namespace number_tmp;

namespace stat_graphics {

	namespace {
		/**
		 * @brief Score value initial x coordinate
		 *
		 */
		const static int score_init_x = 0;

		/**
		 * @brief Score value initial y coordinate
		 *
		 */
		const static int score_init_y = 0;

	}


	/**
	 * @brief Function: void wrapper_stat_cb()
	 *
	 * Callback datset wrapper
	 */
	void wrapper_stat_cb();

	/**
	 * @brief Function: void display_stat_cb()
	 *
	 * This function is called by the GLUT to display the graphics
	 */
	void display_stat_cb();

	/**
	 * @brief Function: void idle_stat_cb()
	 *
	 * This function call idle of the program
	 */
	void idle_stat_cb();

	/**
	 * @brief Function: void mouse_stat_cb(int button, int state, int x, int y);
	 *
	 * \param button: mouse button pressed
	 * \param state: state of mouse button pressed
	 * \param x: x coordinate of the mouse button pressed
	 * \param y: y coordinate of the mouse button pressed
	 *
	 * This function sets mouse button function
	 */
	void mouse_stat_cb(int button, int state, int x, int y);

	/**
	 * @brief Function: void specialkey_stat_cb(int key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function sets mouse button function
	 */
	void specialkey_stat_cb(int key, int x, int y);

	/**
	 * @brief Function: void keyboard_stat_cb(unsigned char key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function assigns a function to some keys of the keyboard
	 */
	void keyboard_stat_cb(unsigned char key, int x, int y);

	/**
	 * @brief Function: stat_pixel_type * get_stat_pixel_array(int & win_width, int & win_height)
	 *
	 * \param win_width: width of the reshaped window
	 * \param win_height: height of the reshaped window
	 *
	 * \return Return the pointer to the array of pixels to draw
	 *
	 * This function
	 * - fill window background with the designated colour
	 * - returns the pointer to the array of pixels to draw
	 */
	template <typename stat_pixel_type>
	stat_pixel_type * get_stat_pixel_array(int & win_width, int & win_height);

	/**
	 * @brief Function: void draw_snake(stat_pixel_type * & win_width, int & win_height)
	 *
	 * \param win_height: height of the reshaped window
	 * \param win_width: width of the reshaped window
	 * \param pixels: pointer to pixels to draw passed by reference
	 * \param init_x: x coordinate of pixel the number starts
	 * \param init_y: y coordinate of pixel the number starts
	 * \param value: value to draw
	 *
	 * This function returns the pointer to the array of pixels to draw
	 */
	template <typename stat_pixel_type>
	void draw_stat(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const int & value);

}

template <typename stat_pixel_type>
stat_pixel_type * stat_graphics::get_stat_pixel_array (int & win_width, int & win_height) {

	int win_area = win_width*win_height;

	stat_pixel_type * pixels = new stat_pixel_type[graphics_utils::no_colours*win_area];
	if (pixels == nullptr) {
		LOG_ERROR("Can't allocate memory for stat pixels array");
	}

	stat_pixel_type * colour = graphics_utils::get_pixel_colour<stat_pixel_type> (graphics_utils::palette_e::BLACK);

	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * pixel_loc + colour_idx] = colour[colour_idx];
			}

		}

	}

	delete [] colour;

	stat_graphics::draw_stat<stat_pixel_type> (pixels, win_width, win_height, stat_graphics::score_init_x, stat_graphics::score_init_y, 123);

	return pixels;

}

template <typename stat_pixel_type>
void stat_graphics::draw_stat(stat_pixel_type * & pixels, const int & win_width, const int & win_height, const int & init_x, const int & init_y, const int & value) {

	std::string value_s (to_string(value));

	for (unsigned i=0; i < value_s.length(); i++) {
		char digit = value_s.at(i);
		int x_start = init_x + number_tmp::num_tiles_width*number_tmp::tile_width;
		int y_start = init_y;
		number_tmp::draw_digit<stat_pixel_type>(pixels, win_width, win_height, x_start, y_start, digit);
	}

}

#endif // STAT_GRAPHICS_H
