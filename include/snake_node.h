#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H
/**
 * @copyright
 * @file snake_node.h
 * @author Andrea Gianarda
 * @date 03rd of March 2019
 * @brief Snake node header file
*/

#include "graphics_utils.h"

namespace snake_node {

	/** @defgroup SnakeNodeGroup Snake Node Doxygen Group
	 *  Snake Node functions and classes
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

	std::ostream& operator<< (std::ostream& os, direction_e direction);

	/**
	 * @brief Initial speed
	 *
	 */
	const static snake_node::direction_e init_direction = snake_node::direction_e::RIGHT;


	class SnakeUnit {
		public:
			// Constructor
			SnakeUnit(int centre_x = 0, int centre_y = 0, snake_node::direction_e snake_direction = snake_node::init_direction, graphics_utils::palette_e snake_colour = graphics_utils::palette_e::BLACK): x_centre(centre_x), y_centre(centre_y), direction(snake_direction), colour(snake_colour) {
				std::string pretext ("Snake Unit Constructor");
				snake_node::SnakeUnit::print_info(log::verb_level_e::LOW, pretext);
			};

			SnakeUnit(const SnakeUnit& copy) : x_centre(copy.x_centre), y_centre(copy.y_centre), direction(copy.direction), colour(copy.colour) {
				std::string pretext ("Snake Unit Copy Constructor");
				snake_node::SnakeUnit::print_info(log::verb_level_e::LOW, pretext);
			};

			// Get functions
			int get_x_centre();
			int get_y_centre();
			snake_node::direction_e get_direction();
			graphics_utils::palette_e get_colour();

			// Set functions
			void set_x_centre(int new_x_centre);
			void set_y_centre(int new_y_centre);
			void set_direction(snake_node::direction_e new_direction);
			void set_colour(graphics_utils::palette_e new_colour);

			// Destructor
			~SnakeUnit();

			void print_info(log::verb_level_e verbosity, std::string pretext);

		private:
			int x_centre;
			int y_centre;
			snake_node::direction_e direction;
			graphics_utils::palette_e colour;

		protected:
	};

	class SnakeNode : public SnakeUnit {
		public:
			// Constructor
			SnakeNode(int centre_x = 0, int centre_y = 0, snake_node::direction_e snake_direction = snake_node::init_direction, graphics_utils::palette_e snake_colour = graphics_utils::palette_e::BLACK): SnakeUnit(centre_x, centre_y, snake_direction, snake_colour), prev(nullptr), next(nullptr) {
				std::string pretext ("Snake Node Constructor");
				snake_node::SnakeNode::print_info(log::verb_level_e::LOW, pretext);
			};

			SnakeNode(const SnakeNode& copy) : SnakeUnit(copy), prev(copy.prev), next(copy.next) { LOG_INFO(log::verb_level_e::LOW, "Snake node copy contructor") };

			// Destructor
			~SnakeNode();

			// Get functions
			SnakeNode * & get_next();
			SnakeNode * & get_prev();

			// Set functions
			void set_next(SnakeNode * next_ptr);
			void set_prev(SnakeNode * prev_ptr);

			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			SnakeNode * prev;
			SnakeNode * next;
	};
	/** @} */ // End of SnakeNodeGroup group
}

#endif // SNAKE_NODE_H
