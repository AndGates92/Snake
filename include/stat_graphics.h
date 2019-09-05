#ifndef STAT_GRAPHICS_H
#define STAT_GRAPHICS_H
/**
 * @copyright
 * @file stat_graphics.h
 * @author Andrea Gianarda
 * @date 25th of April 2019
 * @brief Stat graphics header file
*/

#include <exception>

#include "colours.h"
#include "char_lut.h"
#include "settings.h"

/** @defgroup StatGraphicsGroup Statistics graphics Doxygen Group
 *  Statistics graphics functions and classes
 *  @{
 */
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

}

template <typename stat_pixel_type>
stat_pixel_type * stat_graphics::get_stat_pixel_array (int & win_width, int & win_height) {

	int win_area = win_width*win_height;

	stat_pixel_type * pixels = nullptr;
	try {
		pixels = new stat_pixel_type[colours::no_colours*win_area];
	} catch (std::exception& alloc_e) {
		LOG_ERROR("Caught exception ", alloc_e.what(), " when allocating memory for stat pixel array");
	}

	int win_id = 0;
	win_id = glutGetWindow();

	window_obj::WindowObj node (graphics_utils::search_win_id(win_id));
	colours::palette_e background_colour = node.get_colour_bg();

	stat_pixel_type * colour = colours::get_pixel_colour<stat_pixel_type> (background_colour);

	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<colours::no_colours; colour_idx++) {
				pixels[colours::no_colours * pixel_loc + colour_idx] = colour[colour_idx];
			}

		}

	}

	delete [] colour;

	int start_x = stat_graphics::score_init_x;
	int start_y = stat_graphics::score_init_y;

	std::string obj_name ("Score:");
	char_lut::draw_string<stat_pixel_type> (pixels, win_width, win_height, start_x, start_y, obj_name);

	int tile_width = snake_settings.get_tile_width();
	start_x += (obj_name.length()*(char_lut::num_tiles_width*tile_width));

	int score = snake_settings.get_score();
	std::string score_s (std::to_string(score));
	char_lut::draw_string<stat_pixel_type> (pixels, win_width, win_height, start_x, start_y, score_s);

	return pixels;

}
/** @} */ // End of StatGraphicsGroup group

#endif // STAT_GRAPHICS_H
