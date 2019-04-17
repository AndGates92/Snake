#ifndef SETTINGS_H
#define SETTINGS_H
/**
 * @copyright
 * @file settings.h
 * @author Andrea Gianarda
 * @date 06th of February 2019
 * @brief Settings handling header file
*/

#include <fstream>
#include "logging.h"

namespace settings {

	/** @defgroup SettingsGroup Settings Doxygen Group
	 *  Settings functions and classes
	 *  @{
	 */

	class Settings {
		public:
			// Constructor
			Settings(): hard_wall(false), save_filename("./log/savepoint") {
				std::string pretext ("Settings Constructor");
				settings::Settings::print_info(logging::verb_level_e::LOW, pretext);

			};

			// Destructor
			~Settings();

			// Set functions
			void set_hard_wall_flag(bool value);
			void set_save_filename(std::string name);

			// Get functions
			bool get_hard_wall_flag();
			std::string get_save_filename();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			bool hard_wall;
			std::string save_filename;

		protected:
	};
	/** @} */ // End of SettingsGroup group
}

static settings::Settings snake_settings;

#endif // SETTINGS_H
