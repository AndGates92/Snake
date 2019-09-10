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

/** @defgroup WindowGroup Window Doxygen Group
 *  Window functions and classes
 *  @{
 */
namespace window {
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

	/**
	 * @brief Window class
	 *
	 */
	class Window : public basic_object::BasicObject {
		public:
			// Constructor
			/**
			 * @brief Function: Window(std::string window_title = "", std::string type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK)
			 *
			 * \param window_title: title of the window
			 * \param type: type/group the window belongs to
			 * \param window_width: width of the window
			 * \param window_height: height of the window
			 * \param window_x_pos: position on the x coordinate of the window on the screen
			 * \param window_y_pos: position on the y coordinate of the window on the screen
			 * \param background_colour: background colour of the window
			 *
			 * Window constructor
			 */
			explicit Window(std::string window_title = "", std::string type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK): basic_object::BasicObject(type, window_x_pos, window_y_pos, window_width, window_height, background_colour), title(window_title) {
				id = window::Window::create_window(window_title, window_width, window_height, window_x_pos, window_y_pos);
				LOG_INFO(logging::verb_level_e::HIGH, "Constructor of window ", window_title)
			};

			/**
			 * @brief Function: Window(const Window& copy)
			 *
			 * \param copy: Window to copy
			 *
			 * Window copy constructor
			 */
			Window(const Window& copy) : basic_object::BasicObject(copy), title(copy.title), id(copy.id) {
				LOG_INFO(logging::verb_level_e::HIGH, "Copy constructor of window ", copy.title)
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
			 * @brief Function: int get_id() const
			 *
			 * \return window ID
			 *
			 * Get window ID
			 */
			int get_id() const;

			/**
			 * @brief Function: std::string get_title() const
			 *
			 * \return title of the window
			 *
			 * Get title of the window
			 */
			std::string get_title() const;

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

			/**
			 * @brief Function: bool operator== (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload == operator
			 */
			bool operator== (const window::Window & rhs);

			/**
			 * @brief Function: bool operator!= (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload != operator
			 */
			bool operator!= (const window::Window & rhs);

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

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const window::Window & win)
	 *
	 * \param os: output stream
	 * \param win: window
	 *
	 * Overload << operator to print window details
	 */
	std::ostream& operator<< (std::ostream& os, const window::Window & win);

}
/** @} */ // End of WindowGroup group

#endif // WINDOW_H
