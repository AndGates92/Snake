#ifndef WINDOW_H
#define WINDOW_H
/**
 * @copyright
 * @file window.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window header file
*/

#include "logging.h"
#include "colours.h"
#include "basic_object.h"

namespace window {
	/** @defgroup WindowGroup Window Doxygen Group
	 *  Window functions and classes
	 *  @{
	 */
	/**
	 * @brief Window position on the x coordinate
	 *
	 */
	#define WIN_POS_X 50

	/**
	 * @brief Window position on the y coordinate
	 *
	 */
	#define WIN_POS_Y 50

	/**
	 * @brief Length of window title string
	 *
	 */
	#define WIN_NAME_LENGTH_MAX 20

	class Window : public basic_object::BasicObject {
		public:
			// Constructor
			Window(std::string window_title = "", std::string type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK): basic_object::BasicObject(type, window_x_pos, window_y_pos, window_width, window_height, background_colour), title(window_title) {
				id = window::Window::create_window(window_title, window_width, window_height, window_x_pos, window_y_pos);
				std::string pretext ("Window Constructor");
				window::Window::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: Window(const Window& copy)
			 *
			 * \param copy: Window to copy
			 *
			 * Window copy constructor
			 */
			Window(const Window& copy) : basic_object::BasicObject(copy), title(copy.title), id(copy.id) {
				std::string pretext ("Window Copy Constructor");
				window::Window::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			/**
			 * @brief Function: ~Window()
			 *
			 * Destructor of Window
			 */
			~Window();

			/**
			 * @brief Function: void save_data (iofile::File & savefile)
			 *
			 * \param savefile: file to write Window information to
			 *
			 * Save the Window information
			 */
			void save_data (iofile::File & savefile);

			/**
			 * @brief Function: int get_id()
			 *
			 * \return window ID
			 *
			 * Get window ID
			 */
			int get_id();

			/**
			 * @brief Function: std::string get_title()
			 *
			 * \return title of the window
			 *
			 * Get title of the window
			 */
			std::string get_title();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the Window information
			 *
			 * Print Window information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void destroy_window()
			 *
			 * Destroy this window
			 */
			void destroy_window();

		protected:

			/**
			 * @brief Function: int create_window(std::string title, int width, int height, int xpos, int ypos)
			 *
			 * \param title: title of the window
			 * \param width: width of the window
			 * \param height: height of the window
			 * \param xpos: X coordinate of the window
			 * \param ypos: Y coordinate of the window
			 *
			 * \return window ID
			 *
			 * Create window and return window ID
			 */
			int create_window(std::string title, int width, int height, int xpos, int ypos);

		private:
			/**
			 *
			 * @brief Title of the window
			 *
			 */
			std::string title;

			/**
			 *
			 * @brief Window ID
			 *
			 */
			int id;

	};
	/** @} */ // End of WindowGroup group
}

#endif // WINDOW_H
