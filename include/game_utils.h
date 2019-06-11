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
#include "settings.h"
#include "colours.h"

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

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
	 * \param node_heiht: height of the unit
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
	 * \param node_heiht: height of the unit
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
	 * @brief Function: void set_head_dir(snake_utils::direction_e dir);
	 *
	 * \param dir:  direction to set the nead to
	 *
	 * This function sets the head direction
	 */
	void set_head_dir(snake_utils::direction_e dir);

	/**
	 * @brief Function: snake_utils::direction_e get_head_dir();
	 *
	 * \return returns the direction of the head
	 *
	 * This function returns the head direction
	 */
	snake_utils::direction_e get_head_dir();
}

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
