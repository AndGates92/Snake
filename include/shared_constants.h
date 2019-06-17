#ifndef SHARED_CONSTANTS_H
#define SHARED_CONSTANTS_H
/**
 * @copyright
 * @file shared_constants.h
 * @author Andrea Gianarda
 * @date 14th of May 2019
 * @brief Shared constants file
*/

#include <string>
#include "colours.h"

namespace shared_constants {

	/** @defgroup SharedConstantsGroup Shared Constants Doxygen Group
	 *  Shared constants
	 *  @{
	 */

	// Game window
	/**
	 * @brief Game window title
	 *
	 */
	const static std::string game_win_title("game");
	/**
	 * @brief Game window width
	 *
	 */
	const static int game_win_width=1100;
	/**
	 * @brief Game window height
	 *
	 */
	const static int game_win_height=450;
	/**
	 * @brief Game window position on the x coordinate
	 *
	 */
	const static int game_win_pos_x=100;
	/**
	 * @brief Game window position on the y coordinate
	 *
	 */
	const static int game_win_pos_y=50;
	/**
	 * @brief Game window background 
	 *
	 */
	const static colours::palette_e game_win_bg = colours::palette_e::PURPLE;

	// Stat window
	/**
	 * @brief Stat window title
	 *
	 */
	const static std::string stat_win_title("stat");
	/**
	 * @brief Stat window width
	 *
	 */
	const static int stat_win_width=200;
	/**
	 * @brief Stat window height
	 *
	 */
	const static int stat_win_height=50;
	/**
	 * @brief Stat window position on the x coordinate
	 *
	 */
	const static int stat_win_pos_x=1500;
	/**
	 * @brief Stat window position on the y coordinate
	 *
	 */
	const static int stat_win_pos_y=50;
	/**
	 * @brief Stat window background 
	 *
	 */
	const static colours::palette_e stat_win_bg = colours::palette_e::BROWN;

	/**
	 * @brief comment character
	 *
	 */
	const static std::string comment("//");

	/** @} */ // End of SharedConstantsGroup group

}

#endif // SHARED_CONSTANTS_H
