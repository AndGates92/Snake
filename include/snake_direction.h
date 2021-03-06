#ifndef SNAKE_DIRECTION_H
#define SNAKE_DIRECTION_H
/**
 * @copyright
 * @file snake_direction.h
 * @author Andrea Gianarda
 * @date 30th of June 2019
 * @brief Snake direction class header file
*/

#include "logging.h"
#include "snake_utils.h"

/** @defgroup SnakeDirectionGroup Snake Direction Doxygen Group
 *  Snake Direction functions and classes
 *  @{
 */

namespace snake_direction {

	namespace {
		/**
		 * @brief Initial speed
		 *
		 */
		const static snake_utils::direction_e init_direction = snake_utils::direction_e::UNKNOWN;
	}

	/**
	 * @brief SnakeDirection class
	 *
	 */
	class SnakeDirection {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeDirection(snake_utils::direction_e snake_direction = snake_direction::init_direction)
			 *
			 * \param snake_direction: direction of the snake unit
			 *
			 * SnakeDirection constructor
			 */
			explicit SnakeDirection(snake_utils::direction_e snake_direction = snake_direction::init_direction): direction(snake_direction) {
				std::string pretext ("Constructor");
				snake_direction::SnakeDirection::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: SnakeDirection(const SnakeDirection& copy)
			 *
			 * \param copy: SnakeDirection to copy
			 *
			 * SnakeDirection copy constructor
			 */
			SnakeDirection(const SnakeDirection& copy) : direction(copy.direction) {
				std::string pretext ("Copy Constructor");
				snake_direction::SnakeDirection::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			/**
			 * @brief Function: ~SnakeDirection()
			 *
			 * Destructor of SnakeDirection
			 */
			~SnakeDirection();

			// Get functions
			/**
			 * @brief Function: snake_utils::direction_e get_direction() const
			 *
			 * \return Direction of the SnakeDirection
			 *
			 * Get the direction of the SnakeDirection
			 */
			snake_utils::direction_e get_direction() const;

			// Set functions
			/**
			 * @brief Function: void set_direction(snake_utils::direction_e new_direction)
			 *
			 * \param new_direction: direction the SnakeDirection has to be set to
			 *
			 * Set direction of the SnakeDirection
			 */
			void set_direction(snake_utils::direction_e new_direction);

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the SnakeUnit information
			 *
			 * Print SnakeUnit information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:

			/**
			 * @brief direction of the snake
			 *
			 */
			snake_utils::direction_e direction;

		protected:
	};

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const snake_direction::SnakeDirection & dir)
	 *
	 * \param os: output stream
	 * \param dir: direction to print
	 *
	 * Overload << operator to print direction
	 */
	std::ostream& operator<< (std::ostream& os, const snake_direction::SnakeDirection & dir);
}
/** @} */ // End of SnakeDirectionGroup group
#endif // SNAKE_DIRECTION_H
