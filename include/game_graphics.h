#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H
/**
 * @copyright
 * @file game_graphics.h
 * @author Andrea Gianarda
 * @date 27th of February 2019
 * @brief Game graphics header file
*/

#include "graphics_utils.h"

#include "snake_list.h"
#include "obstacle_list.h"
#include "settings.h"

/**
 * @brief GAME_OVER(...)
 *
 * \param ... :       variable number of arguments to provide to log_error
 *
 * Print an error message to std::cerr to terminate the game
 */
#define GAME_OVER(...)\
	std::string dumpfilename (snake_settings.get_dump_filename());\
	game_graphics::save_game(dumpfilename);\
	LOG_ERROR("File ", __FILE__, " at line ", __LINE__, ": ", __VA_ARGS__, "\n");


namespace game_graphics {

	namespace {
		/**
		 * @brief FIeld of view
		 *
		 */
		const static GLfloat zoom = 50.0;

		/**
		 * @brief Near clip
		 *
		 */
		const static GLfloat zNear = 1.0;

		/**
		 * @brief Far clip
		 *
		 */
		const static GLfloat zFar = 1.0;

		/**
		 * @brief pointer to snake elements
		 *
		 */
		static snake_list::SnakeList * snake;

		/**
		 * @brief pointer to snake elements
		 *
		 */
		static obstacle_list::ObstacleList * obstacles;

	}

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
	 * @brief Function: void init_game()
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
	 * @brief Function: void wrapper_game_cb()
	 *
	 * Callback datset wrapper
	 */
	void wrapper_game_cb();

	/**
	 * @brief Function: void display_game_cb()
	 *
	 * This function is called by the GLUT to display the graphics
	 */
	void display_game_cb();

	/**
	 * @brief Function: void reshape_game_cb(int width, int height)
	 *
	 * \param width: width of the reshaped window
	 * \param height: height of the reshaped window
	 *
	 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
	 */
	void reshape_game_cb(int width, int height);

	/**
	 * @brief Function: void idle_game_cb()
	 *
	 * This function call idle of the program
	 */
	void idle_game_cb();

	/**
	 * @brief Function: void mouse_game_cb(int button, int state, int x, int y);
	 *
	 * \param button: mouse button pressed
	 * \param state: state of mouse button pressed
	 * \param x: x coordinate of the mouse button pressed
	 * \param y: y coordinate of the mouse button pressed
	 *
	 * This function sets mouse button function
	 */
	void mouse_game_cb(int button, int state, int x, int y);

	/**
	 * @brief Function: void specialkey_game_cb(int key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function sets mouse button function
	 */
	void specialkey_game_cb(int key, int x, int y);

	/**
	 * @brief Function: void keyboard_game_cb(unsigned char key, int x, int y);
	 *
	 * \param key: key pressed
	 * \param x: x coordinate of the key pressed
	 * \param y: y coordinate of the key pressed
	 *
	 * This function assigns a function to some keys of the keyboard
	 */
	void keyboard_game_cb(unsigned char key, int x, int y);

	/**
	 * @brief Function: void save_game(std::string filename);
	 *
	 * \param filename: file where to save the status
	 *
	 * This function stores all parameters into a file
	 */
	void save_game(std::string filename);

}

template <typename game_pixel_type>
game_pixel_type * game_graphics::get_game_pixel_array (int & win_width, int & win_height) {

	int win_area = win_width*win_height;

	game_pixel_type * pixels = new game_pixel_type[graphics_utils::no_colours*win_area];
	if (pixels == nullptr) {
		LOG_ERROR("Can't allocate memory for pixels array");
	}

	game_pixel_type * colour = graphics_utils::get_pixel_colour<game_pixel_type> (graphics_utils::palette_e::BLACK);

	for (int width_idx=0; width_idx<win_width; width_idx++) {

		for (int height_idx=0; height_idx<win_height; height_idx++) {
			int pixel_loc = height_idx * win_width + width_idx;

			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * pixel_loc + colour_idx] = colour[colour_idx];
			}

		}

	}

	delete [] colour;

	game_graphics::draw_snake<game_pixel_type> (pixels, win_width, win_height);

	game_graphics::draw_obstacles<game_pixel_type> (pixels, win_width, win_height);

	return pixels;

}

template <typename game_pixel_type>
void game_graphics::draw_snake(game_pixel_type * & pixels, int & win_width, int & win_height) {

	int snake_units = snake_settings.get_snake_units();
	game_graphics::snake->draw<game_pixel_type>(pixels, win_width, win_height, snake_units);

}

template <typename game_pixel_type>
void game_graphics::draw_obstacles(game_pixel_type * & pixels, int & win_width, int & win_height) {

	int obs_no = snake_settings.get_obs_no();
	game_graphics::obstacles->draw<game_pixel_type>(pixels, win_width, win_height, obs_no);

}
#endif // SNAKE_GRAPHICS_H
