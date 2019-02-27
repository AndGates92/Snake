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

#endif // SNAKE_GRAPHICS_H
