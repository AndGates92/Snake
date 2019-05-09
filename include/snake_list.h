#ifndef SNAKE_LIST_H
#define SNAKE_LIST_H
/**
 * @copyright
 * @file snake_list.h
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List header file
*/

#include "basic_obj_list.h"
#include "snake_node.h"
#include "snake_utils.h"
#include "colours.h"

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

			void move(const int & speed, const int & win_width, const int & win_height, const snake_utils::direction_e & head_dir);

			void add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_utils::direction_e snake_direction, colours::palette_e snake_colour);

			void check_collision(const int & win_width, const int & win_height);

		protected:
			int change_dir(snake_node::SnakeNode * & snake_node, int win_dim, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_utils::direction_e prev_dir);
			int adj_snake(snake_node::SnakeNode * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_utils::direction_e dir1, snake_utils::direction_e dir2, snake_utils::direction_e curr_dir, int win_dim_mov);
			int compute_centre_distance(int coord1, int coord2, int win_dim, int exp_distance);
			void check_snake_collision();
			#ifdef HARD_WALL
			void check_wall_collision(const int & win_width, const int & win_height);
			#endif // HARD_WALL

		private:
	};
	/** @} */ // End of SnakeListGroup group
}

#endif // SNAKE_LIST_H
