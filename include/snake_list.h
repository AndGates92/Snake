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
#include "snake_utils.h"
#include "snake_unit.h"
#include "colours.h"

/** @defgroup SnakeListGroup Snake List Doxygen Group
 *  Snake List functions and classes
 *  @{
 */
namespace snake_list {
	/**
	 * @brief SnakeList class
	 *
	 */
	class SnakeList : public basic_obj_list::BasicObjList<snake_unit::SnakeUnit> {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeList(std::string name_snake = "Snake")
			 *
			 * \param name_snake: SnakeList name
			 *
			 * SnakeList constructor
			 */
			explicit SnakeList(std::string name_snake = "Snake"): basic_obj_list::BasicObjList<snake_unit::SnakeUnit>(name_snake) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Snake List Contructor")
			};

			/**
			 * @brief Function: SnakeList(const SnakeList& copy)
			 *
			 * \param copy: SnakeList to copy
			 *
			 * SnakeList copy constructor
			 */
			SnakeList(const SnakeList& copy): basic_obj_list::BasicObjList<snake_unit::SnakeUnit>(copy) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Snake List Copy contructor")
			};

			// Destructor
			/**
			 * @brief Function: ~SnakeList()
			 *
			 * Destructor of SnakeList
			 */
			~SnakeList();

			/**
			 * @brief Function: void move(const int & speed, const int & win_width, const int & win_height, const snake_utils::direction_e & head_dir)
			 *
			 * \param speed: speed of the snake
			 * \param win_width: width of the window element
			 * \param win_height: height of the window element
			 * \param head_dir: direction of the head of the snake
			 *
			 * Move snake 
			 */
			void move(const int & speed, const int & win_width, const int & win_height, const snake_utils::direction_e & head_dir);

			/**
			 * @brief Function: void add_element(int centre_x, int centre_y, int snake_width, int snake_height, snake_utils::direction_e snake_direction, colours::palette_e snake_colour)
			 *
			 * \param centre_x: x coordinate of the snake element
			 * \param centre_y: y coordinate of the snake_unit 
			 * \param snake_width: width of the snake element
			 * \param snake_height: height of the snake element
			 * \param snake_direction: direction of the snake element
			 * \param snake_colour: colour of the snake element
			 *
			 * Add element to SnakeList
			 */
			void add_element(int centre_x, int centre_y, int snake_width, int snake_height, snake_utils::direction_e snake_direction, colours::palette_e snake_colour);

			/**
			 * @brief Function: void check_collision(const int & win_width, const int & win_height)
			 *
			 * \param win_width: width of the window element
			 * \param win_height: height of the window element
			 *
			 * Detect collisions between snake and obstacle and wall
			 */
			void check_collision(const int & win_width, const int & win_height);

		protected:
			/**
			 * @brief Function: int change_dir(snake_unit::SnakeUnit * & snake_unit, int win_dim, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_utils::direction_e prev_dir)
			 *
			 * \param snake_unit: snake element to adjust
			 * \param win_dim: window dimension perpendicular the direction of movement of the current element
			 * \param curr_dim: current element dimension
			 * \param prev_dim: previous element dimension
			 * \param curr_coord_mov_dir: coordinate along direction of movement of the current element
			 * \param prev_coord_mov_dir: coordinate along direction of movement of the previous element
			 * \param sign: sign to state whether movement is leading to incrementing to decrementing the coordindate
			 * \param prev_dir: direction of the previous element
			 *
			 * Detect collision between snake and wall 
			 */
			int change_dir(snake_unit::SnakeUnit & snake_unit, int win_dim, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_utils::direction_e prev_dir);

			/**
			 * @brief Function: int adj_snake(snake_unit::SnakeUnit * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_utils::direction_e dir1, snake_utils::direction_e dir2, snake_utils::direction_e curr_dir, int win_dim_mov)
			 *
			 * \param snake_el: snake element to adjust
			 * \param curr_dim: current element dimension
			 * \param prev_dim: previous element dimension
			 * \param curr_coord_mov_dir: coordinate along direction of movement of the current element
			 * \param prev_coord_mov_dir: coordinate along direction of movement of the previous element
			 * \param curr_coord_perp_dir: coordinate perpendicular the direction of movement of the current element
			 * \param prev_coord_perp_dir: coordinate perpendicular the direction of movement of the previous element
			 * \param speed: speed of the snake
			 * \param dir1: first direction
			 * \param dir2: second direction
			 * \param curr_dir: direction of the current element
			 * \param win_dim_mov: window dimension along direction of movement of the current element
			 *
			 * Adjust snake unit coordinate to ensure snake units are always aligned
			 */
			int adj_snake(snake_unit::SnakeUnit & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_utils::direction_e dir1, snake_utils::direction_e dir2, snake_utils::direction_e curr_dir, int win_dim_mov);
			/**
			 * @brief Function: int compute_centre_distance(int coord1, int coord2, int win_dim, int exp_distance)
			 *
			 * \param coord1: first coordinate
			 * \param coord2: second coordinate
			 * \param win_dim: window dimension
			 * \param exp_distance: expected distance
			 *
			 * Compute distance between coordinates
			 */
			int compute_centre_distance(int coord1, int coord2, int win_dim, int exp_distance);

			/**
			 * @brief Function: void check_snake_collision()
			 *
			 * Detect collision between snake and obstacle
			 */
			void check_snake_collision();
			#ifdef HARD_WALL
			/**
			 * @brief Function: void check_wall_collision(const int & win_width, const int & win_height)
			 *
			 * \param win_width: width of the window element
			 * \param win_height: height of the window element
			 *
			 * Detect collision between snake and wall
			 */
			void check_wall_collision(const int & win_width, const int & win_height);
			#endif // HARD_WALL

		private:
	};
}
/** @} */ // End of SnakeListGroup group

#endif // SNAKE_LIST_H
