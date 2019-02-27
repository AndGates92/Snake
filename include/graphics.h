#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 04th of February 2019
 * @brief Log handling header file
*/

namespace graphics {

	void test_graphics();

	void init_graphics(int argc, char** argv);

	void delete_window();

	/**
	 * @brief Function: void wrapper_cb()
	 *
	 * Callback datset wrapper
	 */
	void wrapper_cb();

	/**
	 * @brief Function: void display_cb()
	 *
	 * This function is called by the GLUT to display the graphics
	 */
	void display_cb();

	/**
	 * @brief Function: void reshape_cb(int width, int height)
	 *
	 * \param width: width of the reshaped window
	 * \param height: height of the reshaped window
	 *
	 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
	 */
	void reshape_cb(int width, int height);

	/**
	 * @brief Function: void idle_cb()
	 *
	 * This function call idle of the program
	 */
	void idle_cb();

	/**
	 * @brief Function: void mouse_cb(int button, int state, int x, int y);
	 *
	 * \param button: mouse button pressed
	 * \param state: state of mouse button pressed
	 * \param x: x coordinate of the mouse button pressed
	 * \param y: y coordinate of the mouse button pressed
	 *
	 * This function sets mouse button function
	 */
	void mouse_cb(int button, int state, int x, int y);

	/**
	 * @brief Function: void specialkey_cb(int key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function sets mouse button function
	 */
	void specialkey_cb(int key, int x, int y);

	/**
	 * @brief Function: void keyboard_cb(unsigned char key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function assigns a function to some keys of the keyboard
	 */
	void keyboard_cb(unsigned char key, int x, int y);

}

#endif // GRAPHICS_H
