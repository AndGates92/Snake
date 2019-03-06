#ifndef SNAKE_LIST_H
#define SNAKE_LIST_H
/**
 * @copyright
 * @file snake_list.h
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List header file
*/

#include "snake_node.h"

namespace snake_list {
	/** @defgroup SnakeListGroup Snake List Doxygen Group
	 *  Snake List functions and classes
	 *  @{
	 */

	class SnakeList {
		public:
			// Constructor
			SnakeList(): head(nullptr) { LOG_INFO(log::verb_level_e::LOW, "Snake list contructed") };

			SnakeList(const SnakeList& copy): head(copy.head) { LOG_INFO(log::verb_level_e::LOW, "Snake list copy contructor") };

			// Destructor
			~SnakeList();

			template <typename pixel_type>
			void draw(pixel_type * & pixels);

			void add_node(int centre_x, int centre_y, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour);

			void print_info(log::verb_level_e verbosity, std::string pretext);

		protected:
			void remove_node(snake_node::SnakeNode * & node);

		private:
			snake_node::SnakeNode * head;
	};
	/** @} */ // End of SnakeListGroup group
}

template <typename pixel_type>
void snake_list::SnakeList::draw(pixel_type * & pixels) {

}

#endif // SNAKE_LIST_H
