#ifndef SNAKE_DIRECTION_LIST_H
#define SNAKE_DIRECTION_LIST_H
/**
 * @copyright
 * @file snake_direction_list.h
 * @author Andrea Gianarda
 * @date 2nd of July 2019
 * @brief Snake direction list class header file
*/

#include "basic_list.h"
#include "snake_utils.h"
#include "snake_direction.h"

/** @defgroup SnakeDirectionGroup Snake Direction Doxygen Group
 *  Snake Direction functions and classes
 *  @{
 */
namespace snake_direction_list {

	/**
	 * @brief SnakeDirectionList class
	 *
	 */
	class SnakeDirectionList : public basic_list::BasicList<snake_direction::SnakeDirectionNode> {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeDirectionList(snake_utils::direction_e snake_direction = snake_direction::init_direction)
			 *
			 * SnakeDirectionList constructor
			 */
			SnakeDirectionList(): basic_list::BasicList<snake_direction::SnakeDirectionNode>() {
				std::string pretext ("Constructor");
			};

			/**
			 * @brief Function: SnakeDirectionList(const SnakeDirectionList& copy)
			 *
			 * \param copy: SnakeDirectionList to copy
			 *
			 * SnakeDirectionList copy constructor
			 */
			SnakeDirectionList(const SnakeDirectionList& copy) : basic_list::BasicList<snake_direction::SnakeDirectionNode>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~SnakeDirectionList()
			 *
			 * Destructor of SnakeDirectionList
			 */
			~SnakeDirectionList();

			/**
			 * @brief Function: void add_node(snake_utils::direction_e direction)
			 *
			 * \param direction: direction to add to the linked list
			 *
			 * Add node to the snake_direction_list
			 */
			void add_node(snake_utils::direction_e direction);

		protected:

		private:
	};
}
/** @} */ // End of SnakeDirectionListGroup group

#endif // SNAKE_DIRECTION_LIST_H
