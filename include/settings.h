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
	}


	class Settings {
		public:
			// Constructor
			Settings(): hard_wall(settings::init_hard_wall), save_filename(settings::init_savefilename), speed(settings::init_speed), speed_incr(settings::init_speed_incr) {
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

			// Get functions
			bool get_hard_wall_flag();
			std::string get_save_filename();
			int get_speed();
			int get_speed_incr();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			bool hard_wall;
			std::string save_filename;
			int speed;
			int speed_incr;

		protected:
	};
	/** @} */ // End of SettingsGroup group
}

static settings::Settings snake_settings;

#endif // SETTINGS_H
