#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H
/**
 * @copyright
 * @file snake_node.h
 * @author Andrea Gianarda
 * @date 5th of March 2019
 * @brief Snake Node header file
*/

#include "snake_unit.h"

namespace snake_node {
	/** @defgroup SnakeNodeGroup Snake Node Doxygen Group
	 *  Snake Node functions and classes
	 *  @{
	 */

	class SnakeNode {
		public:
			// Constructor
			SnakeNode(int centre_x = 0, int centre_y = 0, snake_unit::direction_e snake_direction = snake_unit::init_direction, graphics_utils::palette_e snake_colour = graphics_utils::palette_e::RED): node(centre_x, centre_y, snake_direction, snake_colour), prev(nullptr), next(nullptr) {
				std::string pretext ("Snake Node Constructor");
				snake_node::SnakeNode::print_info(log::verb_level_e::LOW, pretext);
			};

			SnakeNode(const SnakeNode& copy) : node(copy.node), prev(copy.prev), next(copy.next) { LOG_INFO(log::verb_level_e::LOW, "Snake node copy contructor") };

			// Destructor
			~SnakeNode();

			// Get functions
			SnakeNode * & get_next();
			SnakeNode * & get_prev();
			snake_unit::SnakeUnit get_node();

			// Set functions
			void set_next(SnakeNode * next_ptr);
			void set_prev(SnakeNode * prev_ptr);
			void set_node(snake_unit::SnakeUnit node);

			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			snake_unit::SnakeUnit node;
			SnakeNode * prev;
			SnakeNode * next;
	};
	/** @} */ // End of SnakeNodeGroup group
}

#endif // SNAKE_NODE_H
