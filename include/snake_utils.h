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

/** @defgroup SnakeUtilsGroup Snake Utility Doxygen Group
 *  Snake Utils functions and classes
 *  @{
 */
namespace snake_utils {

	/**
	 * @brief Directions
	 *
	 */
	typedef enum class direction_type {
		UP,      /**< Up */
		DOWN,    /**< Down */
		LEFT,    /**< Left */
		RIGHT,   /**< Right */
		UNKNOWN  /**< Unknown */
	} direction_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const game_menu::direction_e & direction)
	 *
	 * \param os: output stream
	 * \param direction: direction to be printed
	 *
	 * Overload << operator to print direction
	 */
	std::ostream& operator<< (std::ostream& os, const snake_utils::direction_e & direction);

	/**
	 * @brief Function: snake_utils::direction_e str_to_direction (std::string dir)
	 *
	 * \param dir: input direction string
	 *
	 * \return direction in form of enumerated value
	 *
	 * Converts a string into a direction_e enumerate value
	 */
	snake_utils::direction_e str_to_direction (std::string dir);
}
/** @} */ // End of SnakeUtilsGroup group
#endif // SNAKE_UTILS_H
