#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H
/**
 * @copyright
 * @file snake_graphics.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Snake graphics header file
*/

namespace snake_graphics {

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
	 * @brief Number of colours: 1 means black and white and 3 means RGB
	 *
	 */
	const static int no_colours = 3;

	template <typename pixel_type>
	pixel_type * get_pixel_array (int win_width, int win_height);

	/**
	 * @brief Function: void wrapper_snake_cb()
	 *
	 * Callback datset wrapper
	 */
	void wrapper_snake_cb();

	/**
	 * @brief Function: void display_snake_cb()
	 *
	 * This function is called by the GLUT to display the graphics
	 */
	void display_snake_cb();

	/**
	 * @brief Function: void reshape_snake_cb(int width, int height)
	 *
	 * \param width: width of the reshaped window
	 * \param height: height of the reshaped window
	 *
	 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
	 */
	void reshape_snake_cb(int width, int height);

	/**
	 * @brief Function: void idle_snake_cb()
	 *
	 * This function call idle of the program
	 */
	void idle_snake_cb();

	/**
	 * @brief Function: void mouse_snake_cb(int button, int state, int x, int y);
	 *
	 * \param button: mouse button pressed
	 * \param state: state of mouse button pressed
	 * \param x: x coordinate of the mouse button pressed
	 * \param y: y coordinate of the mouse button pressed
	 *
	 * This function sets mouse button function
	 */
	void mouse_snake_cb(int button, int state, int x, int y);

	/**
	 * @brief Function: void specialkey_snake_cb(int key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function sets mouse button function
	 */
	void specialkey_snake_cb(int key, int x, int y);

	/**
	 * @brief Function: void keyboard_snake_cb(unsigned char key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function assigns a function to some keys of the keyboard
	 */
	void keyboard_snake_cb(unsigned char key, int x, int y);

}

template <typename pixel_type>
pixel_type * get_pixel_array (int win_width, int win_height) { 

	int win_area = win_width*win_height;

	pixel_type * pixels = new pixel_type[snake_graphics::no_colours*win_area];
	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<snake_graphics::no_colours; colour_idx++) {
				pixels[snake_graphics::no_colours * pixel_loc + colour_idx] = (pixel_type) 50*colour_idx;
			}

		}

	}

	return pixels;

}


#endif // SNAKE_GRAPHICS_H
