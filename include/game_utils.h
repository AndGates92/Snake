#ifndef GAME_UTILS_H
#define GAME_UTILS_H
/**
 * @copyright
 * @file game_utils.h
 * @author Andrea Gianarda
 * @date 10th of June 2019
 * @brief Game utils header file
*/

#include "graphics_utils.h"
#include "window_node.h"
#include "snake_list.h"
#include "obstacle_list.h"
#include "snake_direction_list.h"
#include "settings.h"
#include "colours.h"

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>


/** @defgroup GameUtilsGroup Game utility Doxygen Group
 *  Game utility functions and classes
 *  @{
 */

/**
 * @brief GAME_OVER(...)
 *
 * \param ... :       variable number of arguments to provide to log_error
 *
 * Print an error message to std::cerr to terminate the game
 */
#define GAME_OVER(...)\
	std::string dumpfilename (snake_settings.get_dump_filename());\
	game_utils::save_game(dumpfilename);\
	logging::log_info(logging::verb_level_e::ZERO, "File ", __FILE__, " at line ", __LINE__, ": GAME OVER -> ", __VA_ARGS__, "\n");\
	logging::log_error("GAME OVER: ", __VA_ARGS__, "\n");

namespace game_utils {

	/**
	 * @brief Function: void declare_game_var()
	 *
	 * Declare game variables function
	 */
	void declare_game_var();

	/**
	 * @brief Function: void init_game()
	 *
	 * Initialize game function
	 */
	void init_game();

	/**
	 * @brief Function: void init_snake_list()
	 *
	 * Allocate memory for snake_list class
	 */
	void init_snake_list();

	/**
	 * @brief Function: void init_obstacle_list()
	 *
	 * Allocate memory for obstacle_list class
	 */
	void init_obstacle_list();

	/**
	 * @brief Function: void init_game_parameters()
	 *
	 * Initialize game function
	 */
	void init_game_parameters();

	/**
	 * @brief Function: void populate_snake_list()
	 *
	 * Create initial snake units
	 */
	void populate_snake_list();

	/**
	 * @brief Function: void populate_obstacle_list()
	 *
	 * Create initial obstacles
	 */
	void populate_obstacle_list();

	/**
	 * @brief Function: void free_snake_list()
	 *
	 * Free snake units from the heap
	 */
	void free_snake_list();

	/**
	 * @brief Function: void free_obstacle_list()
	 *
	 * Free obstacles from the heap
	 */
	void free_obstacle_list();

	/**
	 * @brief Function: void free_window_list()
	 *
	 * Free windows from the heap
	 */
	void free_window_list();

	/**
	 * @brief Function: snake_list::SnakeList * & get_snake_ptr()
	 *
	 * \return Return the pointer to the head of the snake
	 *
	 * This function returns the pointer to the head of the snake
	 */
	snake_list::SnakeList * & get_snake_ptr();

	/**
	 * @brief Function: obstacle_list::ObstacleList * & get_obstacle_ptr()
	 *
	 * \return Return the pointer to the head of the obstacle list
	 *
	 * This function returns the pointer to the head of the obstacle
	 */
	obstacle_list::ObstacleList * & get_obstacle_ptr();

	/**
	 * @brief Function: game_pixel_type * get_game_pixel_array(int & win_width, int & win_height)
	 *
	 * \param win_width: width of the reshaped window
	 * \param win_height: height of the reshaped window
	 *
	 * \return Return the pointer to the array of pixels to draw
	 *
	 * This function
	 * - fill window background with the designated colour
	 * - returns the pointer to the array of pixels to draw
	 */
	template <typename game_pixel_type>
	game_pixel_type * get_game_pixel_array(int & win_width, int & win_height);

	/**
	 * @brief Function: void draw_snake(game_pixel_type * & win_width, int & win_height)
	 *
	 * \param win_height: height of the reshaped window
	 * \param win_width: width of the reshaped window
	 * \param pixels: pointer to pixels to draw passed by reference
	 *
	 * This function returns the pointer to the array of pixels to draw
	 */
	template <typename game_pixel_type>
	void draw_snake(game_pixel_type * & pixels, int & win_width, int & win_height);

	/**
	 * @brief Function: void draw_obstacles(game_pixel_type * & win_width, int & win_height)
	 *
	 * \param win_height: height of the reshaped window
	 * \param win_width: width of the reshaped window
	 * \param pixels: pointer to pixels to draw passed by reference
	 *
	 * This function returns the pointer to the array of pixels to draw
	 */
	template <typename game_pixel_type>
	void draw_obstacles(game_pixel_type * & pixels, int & win_width, int & win_height);

	/**
	 * @brief Function: bool contact_between_snake_obs()
	 *
	 * \return Return whether there is contact between the snake and the obstacle
	 *
	 * This function returns whether there is contact between the snake and the obstacle
	 */
	bool contact_between_snake_obs();

	/**
	 * @brief Function: void add_obstacle();
	 *
	 * This function adds an obstacle at a random location
	 */
	void add_obstacle();

	/**
	 * @brief Function: void save_game(std::string filename);
	 *
	 * \param filename: file where to save the status
	 *
	 * This function stores all parameters into a file
	 */
	void save_game(std::string filename);

	/**
	 * @brief Function: void free_game_memory();
	 *
	 * This function free memory allocated for snake list, obstacled and delete the window
	 */
	void free_game_memory();

	/**
	 * @brief Function: void add_snake_node (int centre_x, int centre_y, int node_width, int node_height, snake_utils::direction_e dir, colours::palette_e colour);
	 *
	 * \param centre_x:   sentre of the unit in the X coordinate
	 * \param centre_y:   sentre of the unit in the Y coordinate
	 * \param node_width: width of the unit
	 * \param node_height: height of the unit
	 * \param dir:        direction of the unit
	 * \param colour:     background colour
	 *
	 * This function add a new node to the snake list
	 */
	void add_snake_node (int centre_x, int centre_y, int node_width, int node_height, snake_utils::direction_e dir, colours::palette_e colour);

	/**
	 * @brief Function: void add_obs_node (int centre_x, int centre_y, int node_width, int node_height, colours::palette_e colour);
	 *
	 * \param centre_x:   centre of the unit in the X coordinate
	 * \param centre_y:   centre of the unit in the Y coordinate
	 * \param node_width: width of the unit
	 * \param node_height: height of the unit
	 * \param colour:     background colour
	 *
	 * This function add a new node to the obstacle list
	 */
	void add_obs_node (int centre_x, int centre_y, int node_width, int node_height, colours::palette_e colour);

	/**
	 * @brief Function: void set_snake_settings();
	 *
	 * This function sets the settings of the snake pointer
	 */
	void set_snake_settings();

	/**
	 * @brief Function: void choose_dir(snake_utils::direction_e dir1, snake_utils::direction_e dir2, dir_coord_small, dir_coord_big, other_coord_small, other_coord_big);
	 *
	 * \param dir1:                direction number 1 to choose
	 * \param dir2:                direction number 2 to choose
	 * \param dir_coord_small:     coordinate expected to be the smaller along the direction of motion
	 * \param dir_coord_big:       coordinate expected to be the bigger along the direction of motion
	 * \param other_coord_small:   coordinate expected to be the smaller perpendicular to the direction of motion
	 * \param other_coord_big:     coordinate expected to be the bigger perpendicular to the direction of motion
	 *
	 * This function sets the new direction based on current direction and relative position between obstacles and snake
	 */
	void choose_dir(snake_utils::direction_e dir1, snake_utils::direction_e dir2, int dir_coord_small, int dir_coord_big, int other_coord_small, int other_coord_big);

	/**
	 * @brief Function: void auto_change_dir();
	 *
	 * This function changes the direction when automatic ride is on
	 */
	void auto_change_dir();

	/**
	 * @brief Function: void check_snake_collision()
	 *
	 * This function checks that the chosen direction of the head will not lead to a collision
	 */
	void check_snake_collision();

	#ifdef HARD_WALL
	/**
	 * @brief Function: void check_wall_collision(snake_utils::direction_e snake_head_dir)
	 *
	 * \param snake_head_dir: current direction of the snake head
	 *
	 * This function checks that the chosen direction of the head will collide with the wall
	 */
	void check_wall_collision(snake_utils::direction_e snake_head_dir);

	/**
	 * @brief Function: bool wall_crossing(int coord_obj, int reference, int increment, bool min)
	 *
	 * \param coord_obj: coordinate of the object to compare
	 * \param reference: reference coordinate
	 * \param increment: value to add or substract from coord_obj
	 * \param min: flag to know whether it is a minimum or a maximum
	 *
	 * This function checks if a wall will be hit in the next step
	 */
	bool wall_crossing(int coord_obj, int reference, int increment, bool min);
	#endif // HARD_WALL

	/**
	 * @brief Function: void populate_flags_snake(snake_direction_list::SnakeDirectionList * & dir_list, int & left_dist, int & right_dist, int & up_dist, int & down_dist)
	 *
	 * \param dir_list: sequence of directions of snake units
	 * \param left_dist: flag indicating if there is a snake unit on the left of the head
	 * \param right_dist: flag indicating if there is a snake unit on the right of the head
	 * \param up_dist: flag indicating if there is a snake unit above the head
	 * \param down_dist: flag indicating if there is a snake unit below the head
	 *
	 * This function populates the flags required to check if the chosen direction of the head will not lead to a collision
	 */
	void populate_flags_snake(snake_direction_list::SnakeDirectionList * & dir_list, int & left_dist, int & right_dist, int & up_dist, int & down_dist);

	/**
	 * @brief Function: void populate_flags_obs(int & left_dist, int & right_dist, int & up_dist, int & down_dist)
	 *
	 * \param left_dist: distance between snake head and obstacles on the left of the head
	 * \param right_dist: distance between snake head and obstacles on the right of the head
	 * \param up_dist: distance between snake head and obstacles above the head
	 * \param down_dist: distance between snake head and obstacles below the head
	 *
	 * This function populates the flags required to check if the chosen direction of the head will not lead to a collision
	 */
	void populate_flags_obs(int & left_dist, int & right_dist, int & up_dist, int & down_dist);

	/**
	 * @brief Function: snake_utils::direction_e * populate_dirs(snake_direction_list::SnakeDirectionList * dir_list)
	 *
	 * \param dir_list: sequence of directions of snake units
	 *
	 * \return returns the list of useful directions
	 *
	 * This function populates the directions required to ensure the likelihood of a collision is minimal
	 */
	snake_utils::direction_e * populate_dirs(snake_direction_list::SnakeDirectionList * dir_list);

	/**
	 * @brief Function: void set_dir_no_collision(snake_utils::direction_e dir1, int snake_dist_dir2, int obs_dist_dir2, snake_utils::direction_e dir2, int snake_dist_dir2, int obs_dist_dir2, snake_utils::direction_e * dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist)
	 *
	 * \param dir1: first possible direction to check collision risk for
	 * \param snake_dist_dir1: distance between snake units first possible direction
	 * \param obs_dist_dir1: distance between snake and obstacle on the first possible direction
	 * \param dir2: first possible direction to check collision risk for
	 * \param snake_dist_dir2: distance between snake units second possible direction
	 * \param obs_dist_dir2: distance between snake and obstacle on the second possible direction
	 * \param dirs: useful directions required to make a decision on the next move
	 * \param snake_left_dist: flag indicating if there is a snake unit on the left of the head
	 * \param snake_right_dist: flag indicating if there is a snake unit on the right of the head
	 * \param snake_up_dist: flag indicating if there is a snake unit above the head
	 * \param snake_down_dist: flag indicating if there is a snake unit below the head
	 * \param obs_left_dist: flag indicating if there is an obstacle on the left of the head
	 * \param obs_right_dist: flag indicating if there is an obstacle on the right of the head
	 * \param obs_up_dist: flag indicating if there is an obstacle above the head
	 * \param obs_down_dist: flag indicating if there is an obstacle below the head
	 *
	 * This function sets the less likely direction that can cause a collision
	 */
	void set_dir_no_collision(snake_utils::direction_e dir1, int snake_dist_dir1, int obs_dist_dir1, snake_utils::direction_e dir2, int snake_dist_dir2, int obs_dist_dir2, snake_utils::direction_e * dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist);

	/**
	 * @brief Function: bool unit_in_trajectory(snake_utils::direction_e dir, snake_utils::direction_e * dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist)
	 *
	 * \param dir: direction to check collision risk for
	 * \param dirs: useful directions required to make a decision on the next move
	 * \param snake_left_dist: flag indicating if there is a snake unit on the left of the head
	 * \param snake_right_dist: flag indicating if there is a snake unit on the right of the head
	 * \param snake_up_dist: flag indicating if there is a snake unit above the head
	 * \param snake_down_dist: flag indicating if there is a snake unit below the head
	 * \param obs_left_dist: flag indicating if there is an obstacle on the left of the head
	 * \param obs_right_dist: flag indicating if there is an obstacle on the right of the head
	 * \param obs_up_dist: flag indicating if there is an obstacle above the head
	 * \param obs_down_dist: flag indicating if there is an obstacle below the head
	 *
	 * \return returns whether there is a snake unit in the head trajectory
	 *
	 * This function flags collision risk, i.e. when the head is heading towards a snake unit
	 */
	bool unit_in_trajectory(snake_utils::direction_e dir, snake_utils::direction_e * dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist);

	/**
	 * @brief Function: void game_utils::get_boundaries(ptr_t * ptr, int & x_centre, int & x_min, int & x_max, int & y_centre, int & y_min, int & y_max)
	 *
	 * \param ptr: pointer to extract informations from
	 * \param x_centre: x coordinate of the centre
	 * \param x_min: minimum x coordinate
	 * \param x_max: maximum x coordinate
	 * \param y_centre: y coordinate of the centre
	 * \param y_min: minimum y coordinate
	 * \param y_max: maximum y coordinate
	 *
	 * This function computes the boundaries of an object
	 */
	template <typename ptr_t>
	void get_boundaries(ptr_t * ptr, int & x_centre, int & x_min, int & x_max, int & y_centre, int & y_min, int & y_max);

	/**
	 * @brief Function: void game_utils::get_coord_range(int centre, int dim, int & min_coord, int & max_coord)
	 *
	 * \param centre: coordinate of the centre
	 * \param min_coord: minimum coordinate
	 * \param max_coord: maximum coordinate
	 *
	 * This function computes the boundaries of an object
	 */
	void get_coord_range(int centre, int dim, int & min_coord, int & max_coord);

	/**
	 * @brief Function: void set_head_dir(snake_utils::direction_e dir);
	 *
	 * \param dir: direction to set the nead to
	 *
	 * This function sets the head direction
	 */
	void set_head_dir(snake_utils::direction_e dir);

	/**
	 * @brief Function: bool coord_overlap(int coord1_min, int coord1_max, int coord2_min, int coord2_max)
	 *
	 * \param coord1_min: minimum value of coordinate1
	 * \param coord1_max: maximum value of coordinate1
	 * \param coord2_min: minimum value of coordinate2
	 * \param coord2_max: maximum value of coordinate2
	 *
	 * \return returns whether coordinate1 overlaps coordinate2
	 *
	 * This function flags whether here is an overlap beteen coordinate1 and coordinate2 ranges
	 */
	bool coord_overlap(int coord1_min, int coord1_max, int coord2_min, int coord2_max);

	/**
	 * @brief Function: void update_dist(int coord1, int coord2, int avg_dim, int & dist_1l2, int & dist_1s2)
	 *
	 * \param coord1: coordinate1
	 * \param coord2: coordinate2
	 * \param avg_dim: average dimension
	 * \param dist_1l2: distance to update if coordinate1 is larger than coordinate2
	 * \param dist_1s2: distance to update if coordinate1 is smaller than coordinate2
	 *
	 * This function update distances between head and unit
	 */
	void update_dist(int coord1, int coord2, int avg_dim, int & dist_1l2, int & dist_1s2);

	/**
	 * @brief Function: snake_utils::direction_e get_head_dir();
	 *
	 * \return returns the direction of the head
	 *
	 * This function returns the head direction
	 */
	snake_utils::direction_e get_head_dir();
}

/** @} */ // End of GameUtilsGroup group

template <typename game_pixel_type>
game_pixel_type * game_utils::get_game_pixel_array (int & win_width, int & win_height) {

	int win_area = win_width*win_height;

	game_pixel_type * pixels = new game_pixel_type[colours::no_colours*win_area];
	if (pixels == nullptr) {
		LOG_ERROR("Can't allocate memory for game pixels array");
	}

	int win_id = glutGetWindow();

	window_node::WindowNode * node (graphics_utils::search_win_id(win_id));
	colours::palette_e background_colour = node->get_colour_bg();

	game_pixel_type * colour = colours::get_pixel_colour<game_pixel_type> (background_colour);

	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<colours::no_colours; colour_idx++) {
				pixels[colours::no_colours * pixel_loc + colour_idx] = colour[colour_idx];
			}

		}

	}

	delete [] colour;

	game_utils::draw_snake<game_pixel_type> (pixels, win_width, win_height);

	game_utils::draw_obstacles<game_pixel_type> (pixels, win_width, win_height);

	return pixels;

}

template <typename game_pixel_type>
void game_utils::draw_snake(game_pixel_type * & pixels, int & win_width, int & win_height) {

	int snake_units = snake_settings.get_snake_units();
	snake_list::SnakeList * snake_ptr (game_utils::get_snake_ptr());
	snake_ptr->draw<game_pixel_type>(pixels, win_width, win_height, snake_units);

}

template <typename game_pixel_type>
void game_utils::draw_obstacles(game_pixel_type * & pixels, int & win_width, int & win_height) {

	int obs_no = snake_settings.get_obs_no();
	obstacle_list::ObstacleList * obs_ptr(game_utils::get_obstacle_ptr());
	obs_ptr->draw<game_pixel_type>(pixels, win_width, win_height, obs_no);

}
#endif // GAME_UTILS_H
