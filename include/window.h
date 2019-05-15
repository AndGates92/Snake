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

			Window(const Window& copy) : basic_object::BasicObject(copy), title(copy.title), id(copy.id) {
				std::string pretext ("Window Copy Constructor");
				window::Window::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			~Window();

			void save_data (iofile::File & savefile);

			int get_id();
			std::string get_title();
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			void destroy_window();

		protected:
			int create_window(std::string title, int width, int height, int xpos, int ypos);

		private:
			std::string title;
			int id;

	};
	/** @} */ // End of WindowGroup group
}

#endif // WINDOW_H
