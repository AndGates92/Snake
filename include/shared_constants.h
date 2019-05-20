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
	// Game window
	const static std::string game_win_title("game");
	const static int game_win_width=1100;
	const static int game_win_height=450;
	const static int game_win_pos_x=100;
	const static int game_win_pos_y=50;
	const static colours::palette_e game_win_bg = colours::palette_e::PURPLE;

	// Stat window
	const static std::string stat_win_title("stat");
	const static int stat_win_width=200;
	const static int stat_win_height=50;
	const static int stat_win_pos_x=1500;
	const static int stat_win_pos_y=50;
	const static colours::palette_e stat_win_bg = colours::palette_e::BROWN;
}

#endif // SHARED_CONSTANTS_H
