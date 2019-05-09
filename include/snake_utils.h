#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H
/**
 * @copyright
 * @file snake_utils.h
 * @author Andrea Gianarda
 * @date 03rd of March 2019
 * @brief Snake utility header file
*/

#include <ostream>

namespace snake_utils {

	/** @defgroup SnakeUtilsGroup Snake Utility Doxygen Group
	 *  Snake Utils functions and classes
	 *  @{
	 */

	/**
	 * @brief Directions
	 *
	 */
	typedef enum class direction_type {
		UP,
		DOWN,
		LEFT,
		RIGHT
	} direction_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, game_menu::direction_e direction)
	 *
	 * \param os: output stream
	 * \param direction: direction to be printed
	 *
	 * Overload << operator to print direction 
	 */
	std::ostream& operator<< (std::ostream& os, snake_utils::direction_e direction);
	/** @} */ // End of SnakeUtilsGroup group
}
#endif // SNAKE_UTILS_H
