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

namespace window_obj {
	/** @defgroup WindowObjectGroup Window Object Doxygen Group
	 *  Window Object functions and classes
	 *  @{
	 */

	class WindowObj {
		public:
			// Constructor
			WindowObj(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK): drawing(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour), action_list(window_title) {
				std::string pretext ("Window Object Constructor");
				window_obj::WindowObj::print_info(logging::verb_level_e::LOW, pretext);
			};

			WindowObj(const WindowObj& copy): drawing(copy.drawing), action_list(copy.action_list) {
				std::string pretext ("Window Object Constructor");
				window_obj::WindowObj::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			~WindowObj();
			void destroy_obj();

			void save_data (iofile::File & savefile);

			int get_win_id();
			std::string get_win_title();
			int get_menu_id();
			colours::palette_e get_colour_bg();
			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			window::Window drawing;
			menu::Menu action_list;
	};
	/** @} */ // End of WindowObjectGroup group
}

#endif // WINDOW_OBJ_H
