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
#include "basic_obj_list.h"
#include "snake_node.h"

namespace snake_list {
	/** @defgroup SnakeListGroup Snake List Doxygen Group
	 *  Snake List functions and classes
	 *  @{
	 */

	class SnakeList : public basic_obj_list::BasicObjList<snake_node::SnakeNode> {
		public:
			// Constructor
			SnakeList(std::string name_snake = "Snake"): basic_obj_list::BasicObjList<snake_node::SnakeNode>(name_snake) { LOG_INFO(logging::verb_level_e::LOW, "Contructor") };

			SnakeList(const SnakeList& copy): basic_obj_list::BasicObjList<snake_node::SnakeNode>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~SnakeList();

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int & win_width);
			void move(int speed, int win_width, int win_height, snake_node::direction_e head_dir);

			void add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour);

		protected:
			int change_dir(snake_node::SnakeNode * & snake_node, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_node::direction_e prev_dir);
			int adj_snake(snake_node::SnakeNode * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_node::direction_e dir1, snake_node::direction_e dir2);

		private:
	};
	/** @} */ // End of SnakeListGroup group
}

template <typename pixel_type>
void snake_list::SnakeList::draw(pixel_type * & pixels, int & win_width) {
	snake_node::SnakeNode * snake_node = this->get_head();

	while (snake_node != nullptr) {

		snake_node->draw(pixels, win_width);

		snake_node = snake_node->get_next();

	}

}

#endif // SNAKE_LIST_H
