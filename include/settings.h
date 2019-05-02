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
#include "colours.h"

namespace settings {

	/** @defgroup SettingsGroup Settings Doxygen Group
	 *  Settings functions and classes
	 *  @{
	 */

	/**
	 * @brief Game status
	 *
	 */
	typedef enum class game_status_list {
		RUNNING,
		PAUSED,
		RESTART,
		EXIT
	} game_status_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, settings::game_status_e game_status)
	 *
	 * \param os: output stream
	 * \param game_status: game status to be printed
	 *
	 * Overload << operator to print game status
	 */
	std::ostream& operator<< (std::ostream& os, settings::game_status_e game_status);

	namespace {
		/**
		 * @brief Initial name of file where data is saved
		 *
		 */
		const static std::string init_savefilename = "./log/savepoint";

		/**
		 * @brief Initial name of file where data is dumed upon exit or gameover
		 *
		 */
		const static std::string init_dumpfilename = "./log/dump";

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
		 * @brief Initial colour of the snake
		 *
		 */
		const static colours::palette_e init_snake_colour = colours::palette_e::GREEN;

		/**
		 * @brief Initial colour of the obstacles
		 *
		 */
		const static colours::palette_e init_obs_colour = colours::palette_e::PINK;

		/**
		 * @brief Initial game status
		 *
		 */
		settings::game_status_e init_game_status = settings::game_status_e::RUNNING;

		/**
		 * @brief Initial width of tiles of stat window
		 *
		 */
		const static int init_tile_width = 5;

		/**
		 * @brief Initial height of tiles of stat window
		 *
		 */
		const static int init_tile_height = 5;

		/**
		 * @brief Initial value of score
		 *
		 */
		const static int init_score = 0;
	}


	class Settings {
		public:
			// Constructor
			Settings(): hard_wall(settings::init_hard_wall), dump_filename(settings::init_dumpfilename), save_filename(settings::init_savefilename), game_status(init_game_status), speed(settings::init_speed), speed_incr(settings::init_speed_incr), node_height(settings::init_node_height), node_width(settings::init_node_width), snake_units(settings::init_snake_units), obs_no(settings::init_obs_no), head_centre_x(settings::init_head_centre_x), head_centre_y(settings::init_head_centre_y), head_dir(settings::init_head_dir), snake_colour(settings::init_snake_colour), obs_colour(settings::init_obs_colour), tile_height(settings::init_tile_height), tile_width(settings::init_tile_width), score(settings::init_score) {
				std::string pretext ("Settings Constructor");
				settings::Settings::print_info(logging::verb_level_e::LOW, pretext);

			};

			// Destructor
			~Settings();

			// Set functions
			void set_hard_wall_flag(bool value);
			void set_dump_filename(std::string name);
			void set_save_filename(std::string name);
			void set_game_status(settings::game_status_e game_status_new);
			void set_speed(int value);
			void set_speed_incr(int value);
			void set_node_height(int value);
			void set_node_width(int value);
			void set_snake_units(int value);
			void set_obs_no(int value);
			void set_head_centre_x(int value);
			void set_head_centre_y(int value);
			void set_head_dir(snake_node::direction_e value);
			void set_snake_colour(colours::palette_e new_colour);
			void set_obs_colour(colours::palette_e new_colour);
			void set_tile_height(int value);
			void set_tile_width(int value);
			void set_score(int value);

			// Get functions
			bool get_hard_wall_flag();
			std::string get_dump_filename();
			std::string get_save_filename();
			settings::game_status_e get_game_status();
			int get_speed();
			int get_speed_incr();
			int get_node_height();
			int get_node_width();
			int get_snake_units();
			int get_obs_no();
			int get_head_centre_x();
			int get_head_centre_y();
			snake_node::direction_e get_head_dir();
			colours::palette_e get_snake_colour();
			colours::palette_e get_obs_colour();
			int get_tile_height();
			int get_tile_width();
			int get_score();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			bool hard_wall;
			std::string dump_filename;
			std::string save_filename;
			settings::game_status_e game_status;
			int speed;
			int speed_incr;
			int node_height;
			int node_width;
			int snake_units;
			int obs_no;
			int head_centre_x;
			int head_centre_y;
			snake_node::direction_e head_dir;
			colours::palette_e snake_colour;
			colours::palette_e obs_colour;
			int tile_height;
			int tile_width;
			int score;

		protected:
	};
	/** @} */ // End of SettingsGroup group
}

extern settings::Settings snake_settings;

#endif // SETTINGS_H
