#ifndef WINDOW_OBJ_H
#define WINDOW_OBJ_H
/**
 * @copyright
 * @file window_obj.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window Object header file
*/

#include "logging.h"
#include "menu.h"
#include "window.h"
#include "colours.h"

/** @defgroup WindowObjectGroup Window Object Doxygen Group
 *  Window Object functions and classes
 *  @{
 */
namespace window_obj {
	/**
	 * @brief WindowObj class
	 *
	 */
	class WindowObj {
		public:
			// Constructor
			/**
			 * @brief Function: WindowObj(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK)
			 *
			 * \param window_title: title of the window
			 * \param window_type: type/group the window belongs to
			 * \param window_width: width of the window
			 * \param window_height: height of the window
			 * \param window_x_pos: position on the x coordinate of the window on the screen
			 * \param window_y_pos: position on the y coordinate of the window on the screen
			 * \param background_colour: background colour of the window
			 *
			 * WindowObj constructor
			 */
			WindowObj(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK): drawing(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour), action_list(window_title) {
				std::string pretext ("Window Object Constructor");
				window_obj::WindowObj::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: WindowObj(const WindowObj& copy)
			 *
			 * \param copy: WindowObj to copy
			 *
			 * WindowObj copy constructor
			 */
			WindowObj(const WindowObj& copy): drawing(copy.drawing), action_list(copy.action_list) {
				std::string pretext ("Window Object Constructor");
				window_obj::WindowObj::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			/**
			 * @brief Function: ~WindowObj()
			 *
			 * Destructor of WindowObj
			 */
			~WindowObj();

			/**
			 * @brief Function: void destroy_obj()
			 *
			 * Destroy this WindowObj
			 */
			void destroy_obj();

			/**
			 * @brief Function: void save_data (iofile::File & savefile)
			 *
			 * \param savefile: file to write WindowObj information to
			 *
			 * Save the WindowObj information
			 */
			void save_data (iofile::File & savefile);

			/**
			 * @brief Function: int get_win_id()
			 *
			 * \return window ID
			 *
			 * Get window ID
			 */
			int get_win_id();

			/**
			 * @brief Function: std::string get_win_title()
			 *
			 * \return window title
			 *
			 * Get window title
			 */
			std::string get_win_title();

			/**
			 * @brief Function: int get_menu_id()
			 *
			 * \return menu ID
			 *
			 * Get menu ID
			 */
			int get_menu_id();

			/**
			 * @brief Function: colours::palette_e get_colour_bg()
			 *
			 * \return background colour of the window
			 *
			 * Get background colour of the window
			 */
			colours::palette_e get_colour_bg();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the WindowObj information
			 *
			 * Print WindowObj information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: bool operator== (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload == operator
			 */
			bool operator== (const window_obj::WindowObj & rhs);

			/**
			 * @brief Function: bool operator!= (const window_obj::WindowObj & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload != operator
			 */
			bool operator!= (const window_obj::WindowObj & rhs);

		protected:

		private:
			/**
			 *
			 * @brief Window
			 *
			 */
			window::Window drawing;

			/**
			 *
			 * @brief Menu
			 *
			 */
			menu::Menu action_list;
	};
}
/** @} */ // End of WindowObjectGroup group

#endif // WINDOW_OBJ_H
