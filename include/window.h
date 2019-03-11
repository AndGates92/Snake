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

	class Window {
		public:
			// Constructor
			Window(std::string window_title = "", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (*WrapperFunc)() = nullptr): title(window_title), width(window_width), height(window_height), pos_x(window_x_pos), pos_y(window_y_pos) {
				id = window::Window::create_window(title, width, height, pos_x, pos_y, WrapperFunc);
				std::string pretext ("Window Constructor");
				window::Window::print_info(logging::verb_level_e::LOW, pretext);
			};

			Window(const Window& copy) : title(copy.title), width(copy.width), height(copy.height), pos_x(copy.pos_x), pos_y(copy.pos_y), id(copy.id) {
				std::string pretext ("Window Copy Constructor");
				window::Window::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			~Window();

			int get_id();
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			void destroy_window();

		protected:
			int create_window(std::string title, int width, int height, int xpos, int ypos, void (*WrapperFunc)());

		private:
			std::string title;
			int width;
			int height;
			int pos_x;
			int pos_y;
			int id;
	};
	/** @} */ // End of WindowGroup group
}

#endif // WINDOW_H
