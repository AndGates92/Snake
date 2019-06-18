#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 04th of February 2019
 * @brief Graphics header file
*/

/** @defgroup GraphicsGroup Graphics Doxygen Group
 *  Graphics functions and classes
 *  @{
 */
namespace graphics {


	/**
	 * @brief Function: void init_graphics(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function initialize graphics
	 */
	void init_graphics(int argc, char** argv);

	/**
	 * @brief Function: void add_graphics()
	 *
	 * This function instatiate windows classes and add them to the WindowList
	 */
	void add_graphics();


	/**
	 * @brief Function: void start_game()
	 *
	 * Start the game base don user settings
	 */
	void start_game();

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
	 * This function is idle callback of the program
	 */
	void idle_cb();

	/**
	 * @brief Function: void declare_game()
	 *
	 * This function is run at the start of the program to delcare shared variablesi
	 */
	void declare_game();

	/**
	 * @brief Function: void set_id(int id, std::string type)
	 *
	 * \param id: window ID
	 * \param type: type of teh content of the window
	 *
	 * This function is called to set a window ID when an input file is provided in command line
	 */
	void set_id(int id, std::string type);

}
/** @} */ // End of GraphicsGroup group

#endif // GRAPHICS_H
