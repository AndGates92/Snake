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
#include "snake_utils.h"
#include "colours.h"

/** @defgroup SettingsGroup Settings Doxygen Group
 *  Settings functions and classes
 *  @{
 */
namespace settings {

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
		 * @brief Initial value of automatic ride flag
		 *
		 */
		const static bool init_auto_ride = false;

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
		const static snake_utils::direction_e init_head_dir = snake_utils::direction_e::RIGHT;

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

	/**
	 * @brief Settings class
	 *
	 */
	class Settings {
		public:
			// Constructor
			/**
			 * @brief Function: Settings()
			 *
			 * Constructor of Settings
			 */
			Settings(): auto_ride(settings::init_auto_ride), hard_wall(settings::init_hard_wall), dump_filename(settings::init_dumpfilename), save_filename(settings::init_savefilename), game_status(init_game_status), speed(settings::init_speed), speed_incr(settings::init_speed_incr), node_height(settings::init_node_height), node_width(settings::init_node_width), snake_units(settings::init_snake_units), obs_no(settings::init_obs_no), head_centre_x(settings::init_head_centre_x), head_centre_y(settings::init_head_centre_y), head_dir(settings::init_head_dir), snake_colour(settings::init_snake_colour), obs_colour(settings::init_obs_colour), tile_height(settings::init_tile_height), tile_width(settings::init_tile_width), score(settings::init_score) {
				std::string pretext ("Settings Constructor");
				settings::Settings::print_info(logging::verb_level_e::LOW, pretext);

			};

			// Destructor
			/**
			 * @brief Function: ~Settings()
			 *
			 * Destructor of Settings
			 */
			~Settings();

			// Set functions
			/**
			 * @brief Function: void set_auto_ride_flag(bool value);
			 *
			 * param value: new value of auto ride flag
			 *
			 * Update value of auto ride flag
			 */
			void set_auto_ride_flag(bool value);

			/**
			 * @brief Function: void set_hard_wall_flag(bool value);
			 *
			 * param value: new value of hard wall flag
			 *
			 * Update value of hard wall flag
			 */
			void set_hard_wall_flag(bool value);

			/**
			 * @brief Function: void set_dump_filename(std::string name);
			 *
			 * param value: new value of filename where data are dumped in case of failure
			 *
			 * Update value of filename where data are dumped in case of failure
			 */
			void set_dump_filename(std::string name);

			/**
			 * @brief Function: void set_save_filename(std::string name);
			 *
			 * param value: new value of filename where data are saved upon user request
			 *
			 * Update value of filename where data are saved upon user request
			 */
			void set_save_filename(std::string name);

			/**
			 * @brief Function: void set_game_status(settings::game_status_e game_status_new);
			 *
			 * param value: new value of the status of the game
			 *
			 * Update value of status of the game
			 */
			void set_game_status(settings::game_status_e game_status_new);

			/**
			 * @brief Function: void set_speed(int value);
			 *
			 * param value: new value of the speed
			 *
			 * Update value of the speed the snake is moving at
			 */
			void set_speed(int value);

			/**
			 * @brief Function: void set_speed_incr(int value);
			 *
			 * param value: new value of the speed increment
			 *
			 * Update value of the speed increment
			 */
			void set_speed_incr(int value);

			/**
			 * @brief Function: void set_node_height(int value);
			 *
			 * param value: new value of height of snake nodes
			 *
			 * Update value of height of snake nodes
			 */
			void set_node_height(int value);

			/**
			 * @brief Function: void set_node_width(int value);
			 *
			 * param value: new value of width of snake nodes
			 *
			 * Update value of width of snake nodes
			 */
			void set_node_width(int value);

			/**
			 * @brief Function: void set_snake_units(int value);
			 *
			 * param value: new value of the number of snake units
			 *
			 * Update value of the number of snake units
			 */
			void set_snake_units(int value);

			/**
			 * @brief Function: void set_obs_no(int value);
			 *
			 * param value: new value of the number of obstacles
			 *
			 * Update value of the number of obstacles
			 */
			void set_obs_no(int value);

			/**
			 * @brief Function: void set_head_centre_x(int value);
			 *
			 * param value: new value of x coordinate of the snake head
			 *
			 * Update value of x coordinate of the snake head
			 */
			void set_head_centre_x(int value);

			/**
			 * @brief Function: void set_head_centre_y(int value);
			 *
			 * param value: new value of y coordinate of the snake head
			 *
			 * Update value of y coordinate of the snake head
			 */
			void set_head_centre_y(int value);

			/**
			 * @brief Function: void set_head_dir(snake_utils::direction_e value);
			 *
			 * param value: new value of the direction of the snake head
			 *
			 * Update value of the direction of the snake head
			 */
			void set_head_dir(snake_utils::direction_e value);

			/**
			 * @brief Function: void set_snake_colour(colours::palette_e new_colour);
			 *
			 * param new_colour: new colour of the snake
			 *
			 * Update value of the colour of the snake
			 */
			void set_snake_colour(colours::palette_e new_colour);

			/**
			 * @brief Function: void set_obs_colour(colours::palette_e new_colour);
			 *
			 * param new_colour: new colour of the obstacles
			 *
			 * Update value of the colour of obstacles
w
			 */
			void set_obs_colour(colours::palette_e new_colour);

			/**
			 * @brief Function: void set_tile_height(int value);
			 *
			 * param value: new value of the height of the tile
			 *
			 * Update value of the height of the tile
			 */
			void set_tile_height(int value);

			/**
			 * @brief Function: void set_tile_width(int value);
			 *
			 * param value: new value of the width of the tile
			 *
			 * Update value of the width of the tile
			 */
			void set_tile_width(int value);

			/**
			 * @brief Function: void set_score(int value);
			 *
			 * param value: new value of score
			 *
			 * Update value of the score
			 */
			void set_score(int value);


			// Get functions
			/**
			 * @brief Function: bool get_auto_ride_flag()
			 *
			 * \return value of auto ride flag
			 *
			 * Provide value of auto ride flag
			 */
			bool get_auto_ride_flag();

			/**
			 * @brief Function: bool get_hard_wall_flag()
			 *
			 * \return value of hard wall flag
			 *
			 * Provide value of hard wall flag
			 */
			bool get_hard_wall_flag();

			/**
			 * @brief Function: std::string get_dump_filename()
			 *
			 * \return value of dump_filename
			 *
			 * Provide value of dump_filename
			 */
			std::string get_dump_filename();

			/**
			 * @brief Function: std::string get_save_filename()
			 *
			 * \return value of save_filename
			 *
			 * Provide value of save_filename
			 */
			std::string get_save_filename();

			/**
			 * @brief Function: settings::game_status_e get_game_status()
			 *
			 * \return value of game_status
			 *
			 * Provide value of game_status
			 */
			settings::game_status_e get_game_status();

			/**
			 * @brief Function: int get_speed()
			 *
			 * \return value of speed
			 *
			 * Provide value of speed
			 */
			int get_speed();

			/**
			 * @brief Function: int get_speed_incr()
			 *
			 * \return value of speed increment
			 *
			 * Provide value of speed increment
			 */
			int get_speed_incr();

			/**
			 * @brief Function: int get_node_height()
			 *
			 * \return value of the height of a node
			 *
			 * Provide value of the height of a node
			 */
			int get_node_height();

			/**
			 * @brief Function: int get_node_width()
			 *
			 * \return value of the width of a node
			 *
			 * Provide value of the width of a node
			 */
			int get_node_width();

			/**
			 * @brief Function: int get_snake_units()
			 *
			 * \return value of number of snake units
			 *
			 * Provide value of number of snake units
			 */
			int get_snake_units();

			/**
			 * @brief Function: int get_obs_no()
			 *
			 * \return value of the number of obstacles
			 *
			 * Provide value of the number of obstacles
			 */
			int get_obs_no();

			/**
			 * @brief Function: int get_head_centre_x()
			 *
			 * \return value of the x coordinate of the snake head
			 *
			 * Provide value of the x coordinate of the snake head
			 */
			int get_head_centre_x();

			/**
			 * @brief Function: int get_head_centre_y()
			 *
			 * \return value of the y coordinate of the snake head
			 *
			 * Provide value of the y coordinate of the snake head
			 */
			int get_head_centre_y();

			/**
			 * @brief Function: snake_utils::direction_e get_head_dir()
			 *
			 * \return value of direction of the snake head
			 *
			 * Provide value of direction of the snake head
			 */
			snake_utils::direction_e get_head_dir();

			/**
			 * @brief Function: colours::palette_e get_snake_colour()
			 *
			 * \return value of colour of snakes
			 *
			 * Provide value of colour of snakes
			 */
			colours::palette_e get_snake_colour();

			/**
			 * @brief Function: colours::palette_e get_obs_colour()
			 *
			 * \return value of colour of obstacles
			 *
			 * Provide value of colour of obstacles
			 */
			colours::palette_e get_obs_colour();

			/**
			 * @brief Function: int get_tile_height()
			 *
			 * \return value of the height of tiles
			 *
			 * Provide value of the height of tiles
			 */
			int get_tile_height();

			/**
			 * @brief Function: int get_tile_width()
			 *
			 * \return value of the width of tiles
			 *
			 * Provide value of the width of tiles
			 */
			int get_tile_width();

			/**
			 * @brief Function: int get_score()
			 *
			 * \return value of score
			 *
			 * Provide value of score
			 */
			int get_score();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the Settings information
			 *
			 * Print Settings information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void save_data(iofile::File & savefile)
			 *
			 * \param savefile: filename where to save settings to
			 *
			 * Save Settings information to a file
			 */
			void save_data(iofile::File & savefile);

		private:
			/**
			 * @brief Auto ride flag
			 *
			 */
			bool auto_ride;
			/**
			 * @brief hard wall flag
			 *
			 */
			bool hard_wall;

			/**
			 * @brief dump filename
			 *
			 */
			std::string dump_filename;

			/**
			 * @brief save filename
			 *
			 */
			std::string save_filename;

			/**
			 * @brief game status
			 *
			 */
			settings::game_status_e game_status;

			/**
			 * @brief speed
			 *
			 */
			int speed;

			/**
			 * @brief speed increment
			 *
			 */
			int speed_incr;

			/**
			 * @brief height of a node
			 *
			 */
			int node_height;

			/**
			 * @brief width of a node
			 *
			 */
			int node_width;

			/**
			 * @brief number of snake units
			 *
			 */
			int snake_units;

			/**
			 * @brief number of obstacles
			 *
			 */
			int obs_no;

			/**
			 * @brief x coordinate of the snake head
			 *
			 */
			int head_centre_x;

			/**
			 * @brief y coordinate of the snake head
			 *
			 */
			int head_centre_y;

			/**
			 * @brief head_dir
			 *
			 */
			snake_utils::direction_e head_dir;

			/**
			 * @brief snake_colour
			 *
			 */
			colours::palette_e snake_colour;

			/**
			 * @brief obs_colour
			 *
			 */
			colours::palette_e obs_colour;

			/**
			 * @brief tile_height
			 *
			 */
			int tile_height;

			/**
			 * @brief tile_width
			 *
			 */
			int tile_width;

			/**
			 * @brief score
			 *
			 */
			int score;


		protected:
	};
}
/** @} */ // End of SettingsGroup group

/**
 * @brief Global variable snake_settins
 *
 */
extern settings::Settings snake_settings;

#endif // SETTINGS_H
