#ifndef SETTINGS_H
#define SETTINGS_H
/**
 * @copyright
 * @file settings.h
 * @author Andrea Gianarda
 * @date 17th of April 2019
 * @brief Settings handling header file
*/

#include <fstream>
#include "logging.h"
#include "snake_node.h"
#include "graphics_utils.h"

namespace settings {

	/** @defgroup SettingsGroup Settings Doxygen Group
	 *  Settings functions and classes
	 *  @{
	 */

	namespace {
		/**
		 * @brief Initial name of file where data is saved
		 *
		 */
		const static std::string init_savefilename = "./log/savepoint";

		/**
		 * @brief Initial value of hard wall flag
		 *
		 */
		const static bool init_hard_wall = false;

		/**
		 * @brief Initial speed of snake (in pixels/loop iter)
		 *
		 */
		const static int init_speed = 2;

		/**
		 * @brief Speed increment of snake (in pixels/loop iter)
		 *
		 */
		const static int init_speed_incr = 1;

		/**
		 * @brief Node Height
		 *
		 */
		const static int init_node_height = 10;

		/**
		 * @brief Node Width
		 *
		 */
		const static int init_node_width = 10;

		/**
		 * @brief Initial number of snake units
		 *
		 */
		const static int init_snake_units = 5;

		/**
		 * @brief Initial number of obstacles units
		 *
		 */
		const static int init_obs_no = 1;

		/**
		 * @brief Initial X coordinate of the snake head
		 *
		 */
		const static int init_head_centre_x = 100;

		/**
		 * @brief Initial Y coordinate of the snake head
		 *
		 */
		const static int init_head_centre_y = 100;

		/**
		 * @brief Initial direction of the snake
		 *
		 */
		const static snake_node::direction_e init_head_dir = snake_node::direction_e::RIGHT;

		/**
		 * @brief Initial color of the snake
		 *
		 */
		const static graphics_utils::palette_e init_snake_color = graphics_utils::palette_e::GREEN;

		/**
		 * @brief Initial color of the obstacles
		 *
		 */
		const static graphics_utils::palette_e init_obs_color = graphics_utils::palette_e::PINK;
	}


	class Settings {
		public:
			// Constructor
			Settings(): hard_wall(settings::init_hard_wall), save_filename(settings::init_savefilename), speed(settings::init_speed), speed_incr(settings::init_speed_incr), node_height(settings::init_node_height), node_width(settings::init_node_width), snake_units(settings::init_snake_units), obs_no(settings::init_obs_no), head_centre_x(settings::init_head_centre_x), head_centre_y(settings::init_head_centre_y), head_dir(settings::init_head_dir), snake_color(settings::init_snake_color), obs_color(settings::init_obs_color) {
				std::string pretext ("Settings Constructor");
				settings::Settings::print_info(logging::verb_level_e::LOW, pretext);

			};

			// Destructor
			~Settings();

			// Set functions
			void set_hard_wall_flag(bool value);
			void set_save_filename(std::string name);
			void set_speed(int value);
			void set_speed_incr(int value);
			void set_node_height(int value);
			void set_node_width(int value);
			void set_snake_units(int value);
			void set_obs_no(int value);
			void set_head_centre_x(int value);
			void set_head_centre_y(int value);
			void set_head_dir(snake_node::direction_e value);
			void set_snake_color(graphics_utils::palette_e new_color);
			void set_obs_color(graphics_utils::palette_e new_color);

			// Get functions
			bool get_hard_wall_flag();
			std::string get_save_filename();
			int get_speed();
			int get_speed_incr();
			int get_node_height();
			int get_node_width();
			int get_snake_units();
			int get_obs_no();
			int get_head_centre_x();
			int get_head_centre_y();
			snake_node::direction_e get_head_dir();
			graphics_utils::palette_e get_snake_color();
			graphics_utils::palette_e get_obs_color();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			bool hard_wall;
			std::string save_filename;
			int speed;
			int speed_incr;
			int node_height;
			int node_width;
			int snake_units;
			int obs_no;
			int head_centre_x;
			int head_centre_y;
			snake_node::direction_e head_dir;
			graphics_utils::palette_e snake_color;
			graphics_utils::palette_e obs_color;


		protected:
	};
	/** @} */ // End of SettingsGroup group
}

static settings::Settings snake_settings;

#endif // SETTINGS_H
