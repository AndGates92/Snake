#ifndef STAT_GRAPHICS_H
#define STAT_GRAPHICS_H
/**
 * @copyright
 * @file stat_graphics.h
 * @author Andrea Gianarda
 * @date 25th of April 2019
 * @brief Stat graphics header file
*/

namespace stat_graphics {

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

}

#endif // STAT_GRAPHICS_H
