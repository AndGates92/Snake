#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H
/**
 * @copyright
 * @file game_graphics.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Snake graphics header file
*/

#include "graphics_utils.h"

#include "snake_list.h"

namespace game_graphics {

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

		static snake_list::SnakeList * snake;

		/**
		 * @brief Node Height
		 *
		 */
		const static int snake_node_height = 10;

		/**
		 * @brief Node Width
		 *
		 */
		const static int snake_node_width = 10;

		const static int init_units = 5;

	}

	void init_snake_list();
	void populate_snake_list();

	snake_list::SnakeList * & get_snake_ptr();

	template <typename game_pixel_type>
	game_pixel_type * get_game_pixel_array (int & win_width, int & win_height);

	template <typename game_pixel_type>
	void draw_snake (game_pixel_type * & pixels, int & win_width);

	/**
	 * @brief Function: void wrapper_game_cb()
	 *
	 * Callback datset wrapper
	 */
	void wrapper_game_cb();

	/**
	 * @brief Function: void display_game_cb()
	 *
	 * This function is called by the GLUT to display the graphics
	 */
	void display_game_cb();

	/**
	 * @brief Function: void reshape_game_cb(int width, int height)
	 *
	 * \param width: width of the reshaped window
	 * \param height: height of the reshaped window
	 *
	 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
	 */
	void reshape_game_cb(int width, int height);

	/**
	 * @brief Function: void idle_game_cb()
	 *
	 * This function call idle of the program
	 */
	void idle_game_cb();

	/**
	 * @brief Function: void mouse_game_cb(int button, int state, int x, int y);
	 *
	 * \param button: mouse button pressed
	 * \param state: state of mouse button pressed
	 * \param x: x coordinate of the mouse button pressed
	 * \param y: y coordinate of the mouse button pressed
	 *
	 * This function sets mouse button function
	 */
	void mouse_game_cb(int button, int state, int x, int y);

	/**
	 * @brief Function: void specialkey_game_cb(int key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function sets mouse button function
	 */
	void specialkey_game_cb(int key, int x, int y);

	/**
	 * @brief Function: void keyboard_game_cb(unsigned char key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function assigns a function to some keys of the keyboard
	 */
	void keyboard_game_cb(unsigned char key, int x, int y);

}

template <typename game_pixel_type>
game_pixel_type * game_graphics::get_game_pixel_array (int & win_width, int & win_height) {

	int win_area = win_width*win_height;

	game_pixel_type * pixels = new game_pixel_type[graphics_utils::no_colours*win_area];

	game_pixel_type * colour = graphics_utils::get_pixel_colour<game_pixel_type> (graphics_utils::palette_e::BLACK);

	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * pixel_loc + colour_idx] = colour[colour_idx];
			}

		}

	}

	delete [] colour;

	game_graphics::draw_snake<game_pixel_type> (pixels, win_width);

	return pixels;

}

template <typename game_pixel_type>
void game_graphics::draw_snake (game_pixel_type * & pixels, int & win_width) {

	game_graphics::snake->draw<game_pixel_type>(pixels, win_width);

}

#endif // SNAKE_GRAPHICS_H
