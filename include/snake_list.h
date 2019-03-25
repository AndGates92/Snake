#ifndef SNAKE_LIST_H
#define SNAKE_LIST_H
/**
 * @copyright
 * @file snake_list.h
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List header file
*/

#include "graphics_utils.h"
#include "snake_node.h"

namespace snake_list {
	/** @defgroup SnakeListGroup Snake List Doxygen Group
	 *  Snake List functions and classes
	 *  @{
	 */

	class SnakeList {
		public:
			// Constructor
			SnakeList(): head(nullptr) { LOG_INFO(logging::verb_level_e::LOW, "Snake list contructed") };

			SnakeList(const SnakeList& copy): head(copy.head) { LOG_INFO(logging::verb_level_e::LOW, "Snake list copy contructor") };

			// Destructor
			~SnakeList();

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int & win_width);
			void move(int speed, int win_width, int win_height);

			void add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour);

			void print_info(logging::verb_level_e verbosity, std::string pretext);

			snake_node::SnakeNode * get_head();

			void set_head_direction(snake_node::direction_e direction);

		protected:
			void remove_node(snake_node::SnakeNode * & node);

		private:
			snake_node::SnakeNode * head;
	};
	/** @} */ // End of SnakeListGroup group
}

template <typename pixel_type>
void snake_list::SnakeList::draw(pixel_type * & pixels, int & win_width) {
	snake_node::SnakeNode * snake_node = this->head;

	while (snake_node != nullptr) {

		snake_node->draw(pixels, win_width);

		snake_node = snake_node->get_next();

	}

}

#endif // SNAKE_LIST_H
