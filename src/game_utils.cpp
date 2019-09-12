/**
 * @copyright
 * @file game_utils.cpp
 * @author Andrea Gianarda
 * @date 10th June 2019
 * @brief Game utils functions
 */

#include <iostream>
#include <cmath>
#include <vector>

#include "settings.h"
#include "utility.h"
#include "logging.h"
#include "colours.h"
#include "game_utils.h"
#include "graphics_utils.h"
#include "snake_list.h"
#include "snake_unit.h"
#include "snake_utils.h"

/** @addtogroup GameUtilsGroup
 *
 *  @{
 */
namespace game_utils {

	namespace {
		/**
		 * @brief Direction of the snake head
		 *
		 */
		snake_utils::direction_e head_dir;

		/**
		 * @brief Counter to update direction when automatic ride is on
		 *
		 */
		int auto_ride_count;

		/**
		 * @brief pointer to snake elements
		 *
		 */
		static snake_list::SnakeList snake;

		/**
		 * @brief pointer to snake elements
		 *
		 */
		static obstacle_list::ObstacleList obstacles;

		/**
		 * @brief Value of distance normalized by snake unit between head and unit width for which chanign direction is required
		 *
		 */
		const int min_dist_force_change_dir = 4;

		/**
		 * @brief Initial value of distance on each side
		 *
		 */
		const int dist_init_val = -1;

		/**
		 * @brief Number of directions to extract from direction list to know the next direction
		 *
		 */
		const int num_useful_dirs = 3;
	}
}
/** @} */ // End of addtogroup GameUtilsGroup

void game_utils::init_snake_list() {
	std::string type("Snake");
	game_utils::snake = snake_list::SnakeList(type);
}

void game_utils::init_obstacle_list() {
	std::string type("Obstacle");
	game_utils::obstacles = obstacle_list::ObstacleList(type);
}

snake_list::SnakeList & game_utils::get_snake_ptr() {
	return game_utils::snake;
}

obstacle_list::ObstacleList & game_utils::get_obstacle_ptr() {
	return game_utils::obstacles;
}

void game_utils::populate_snake_list() {
	int centre_x = snake_settings.get_head_centre_x();
	int centre_y = snake_settings.get_head_centre_y();

	int snake_units = snake_settings.get_snake_units();
	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	snake_utils::direction_e snake_head_dir(snake_settings.get_head_dir());
	colours::palette_e colour(snake_settings.get_snake_colour());

	for (int unit_no=0; unit_no < snake_units; unit_no++) {

		game_utils::add_snake_node(centre_x, centre_y, node_width, node_height, snake_head_dir, colour);
		//game_utils::snake.add_element(centre_x, centre_y, game_utils::node_width, game_utils::node_height, game_utils::init_head_dir, (colours::palette_e) unit_no);
		centre_x += node_width;
		//game_utils::snake.add_element(centre_x, centre_y, game_utils::node_width, game_utils::node_height, game_utils::init_head_dir, colours::palette_e::RED);
		//centre_y += game_utils::node_height;

	}

	// Colour snake_head differently to ease debug
	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit & snake_head(snake_vector.at(0));
	snake_head.set_colour(colours::palette_e::YELLOW);

}

void game_utils::set_snake_settings() {

	std::vector<snake_unit::SnakeUnit> snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));
	snake_utils::direction_e snake_head_dir(snake_head.get_direction());
	snake_settings.set_head_dir(snake_head_dir);
	int snake_head_x = snake_head.get_x_centre();
	snake_settings.set_head_centre_x(snake_head_x);
	int snake_head_y = snake_head.get_y_centre();
	snake_settings.set_head_centre_y(snake_head_y);

}

void game_utils::add_snake_node (int centre_x, int centre_y, int node_width, int node_height, snake_utils::direction_e dir, colours::palette_e colour) {
	game_utils::snake.add_element(centre_x, centre_y, node_width, node_height, dir, colour);
}

void game_utils::add_obs_node (int centre_x, int centre_y, int node_width, int node_height, colours::palette_e colour) {
	game_utils::obstacles.add_element(centre_x, centre_y, node_width, node_height, colour);
}

void game_utils::populate_obstacle_list() {

	int obs_no = snake_settings.get_obs_no();

	for (int obs=0; obs < obs_no; obs++) {
		game_utils::add_obstacle();
	}

}

void game_utils::init_game_parameters() {
	game_utils::head_dir = snake_settings.get_head_dir();
	game_utils::auto_ride_count = 0;
}

void game_utils::declare_game_var() {
	game_utils::init_snake_list();
	game_utils::init_obstacle_list();
}

void game_utils::init_game() {
	game_utils::populate_snake_list();
	game_utils::populate_obstacle_list();
}

bool game_utils::contact_between_snake_obs() {

	// Retrieve snake head informations
	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));
	int snake_head_x = snake_head.get_x_centre();
	int snake_head_width = snake_head.get_width();
	int snake_head_x_min = snake_head_x - snake_head_width/2;
	int snake_head_x_max = snake_head_x + snake_head_width/2;
	int snake_head_y = snake_head.get_y_centre();
	int snake_head_height = snake_head.get_height();
	int snake_head_y_min = snake_head_y - snake_head_height/2;
	int snake_head_y_max = snake_head_y + snake_head_height/2;

	// obstacle pointer
	std::vector<obstacle::Obstacle> & obs_vector(game_utils::obstacles.get_vector());

	bool contact = false;

	for (auto curr_node : obs_vector) {
		int obs_x = curr_node.get_x_centre();
		int obs_width = curr_node.get_width();
		int obs_x_min = obs_x - obs_width/2;
		int obs_x_max = obs_x + obs_width/2;
		int obs_y = curr_node.get_y_centre();
		int obs_height = curr_node.get_height();
		int obs_y_min = obs_y - obs_height/2;
		int obs_y_max = obs_y + obs_height/2;

		// Save temporary obstacle
		obstacle::Obstacle node_tmp(curr_node);

		if (
			(
			// snake head X minimum coordinate is between obstacle X minimum and X maximum
			((snake_head_x_min <= obs_x_max) && (snake_head_x_min >= obs_x_min)) ||
			// snake head X maximum coordinate is between obstacle X minimum and X maximum
			((snake_head_x_max <= obs_x_max) && (snake_head_x_max >= obs_x_min))
			) && (
			// snake head Y minimum coordinate is between obstacle Y minimum and X maximum
			((snake_head_y_min <= obs_y_max) && (snake_head_y_min >= obs_y_min)) ||
			// snake head Y maximum coordinate is between obstacle Y minimum and X maximum
			((snake_head_y_max <= obs_y_max) && (snake_head_y_max >= obs_y_min))
			)
		) {

			LOG_INFO(logging::verb_level_e::MEDIUM,"[Contact snake-obstacle] Contact between snake head at (", snake_head_x, ", ", snake_head_y, ") and obstacle at (", obs_x, ", ", obs_y, ")");
			// Delete obstacle after contact
			game_utils::obstacles.remove_element(node_tmp);
			contact = true;
		}
	}

	return contact;
}

void game_utils::add_obstacle() {

	double win_width = 0.0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	int win_width_int = (int) win_width;

	double win_height = 0.0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);
	int win_height_int = (int) win_height;

	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	colours::palette_e colour(snake_settings.get_obs_colour());

	// Random coordinates must be within node_width/2 and (win_width-node_width/2)
	int centre_x = (rand() % (win_width_int - node_width)) + node_width/2;

	// Random coordinates must be within node_height/2 and (win_height-node_height/2)
	int centre_y = (rand() % (win_height_int - node_height)) + node_height/2;

	//game_utils::obstacles.add_element(centre_x, centre_y, game_utils::node_width, game_utils::node_height, colours::palette_e::PURPLE);
	game_utils::add_obs_node(centre_x, centre_y, node_width, node_height, colour);
}

void game_utils::free_obstacle_list() {
	LOG_INFO(logging::verb_level_e::LOW, "Destroy all obstacles");
	LOG_INFO(logging::verb_level_e::LOW, game_utils::obstacles);
	game_utils::obstacles.delete_all_elements();
}

void game_utils::free_snake_list() {
	LOG_INFO(logging::verb_level_e::LOW, "Destroy all snakes");
	LOG_INFO(logging::verb_level_e::LOW, game_utils::snake);
	game_utils::snake.delete_all_elements();
}

void game_utils::free_window_list() {
	LOG_INFO(logging::verb_level_e::DEBUG, "Destroy all windows");
	graphics_utils::delete_all_windows();
}

void game_utils::save_game(std::string filename) {
	// obstacle pointer
	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());

	std::string tmp_filename(filename);
	tmp_filename.append(".tmp");

	utility::file_rename(filename, tmp_filename);
	utility::file_delete(filename);

	LOG_INFO(logging::verb_level_e::DEBUG,"[Save Game] Saving game to file: ", filename);

	iofile::File save(filename, iofile::mode_e::WO);

	int snake_units = snake_settings.get_snake_units();
	int obs_no = snake_settings.get_obs_no();

	int snake_node_cnt = 0;

	snake_settings.save_data(save);

	graphics_utils::save_window(save);

	for (auto curr_snake_node : snake_vector) {
		save.write_ofile("//******************************\n");
		save.write_ofile("// Snake Node ", snake_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		curr_snake_node.save_data(save);

		save.write_ofile("\n");

		// Save temporary obstacle
		snake_node_cnt++;
	}

	ASSERT(snake_node_cnt==snake_units);

	// obstacle pointer
	std::vector<obstacle::Obstacle> & obs_vector(game_utils::obstacles.get_vector());

	int obs_node_cnt = 0;

	for (auto curr_obs_node : obs_vector) {

		save.write_ofile("//******************************\n");
		save.write_ofile("// Obstacle Node ", obs_node_cnt, "\n");
		save.write_ofile("//******************************\n");

		// Save temporary obstacle
		curr_obs_node.save_data(save);

		obs_node_cnt++;
	}

	ASSERT(obs_node_cnt==obs_no);

}

void game_utils::free_game_memory() {
	game_utils::free_obstacle_list();
	game_utils::free_snake_list();
	snake_settings.~Settings();
}

void game_utils::auto_change_dir() {

	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));
	snake_utils::direction_e snake_head_dir(snake_head.get_direction());

	// Coordinates
	int snake_head_x = snake_head.get_x_centre();
	int snake_head_y = snake_head.get_y_centre();

	// Dimensions
	int height = snake_head.get_height();
	int width = snake_head.get_width();

	int speed = snake_settings.get_speed();

	int max_auto_ride_count = 0;

	if ((snake_head_dir == snake_utils::direction_e::LEFT) || (snake_head_dir == snake_utils::direction_e::RIGHT)) {
		float result = ((float)width)/((float)speed);
		max_auto_ride_count = (int) floor(result);
	} else if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
		float result = ((float)height)/((float)speed);
		max_auto_ride_count = (int) floor(result);
	}

	std::vector<obstacle::Obstacle> & obs_vector(game_utils::obstacles.get_vector());
	obstacle::Obstacle obs_node(obs_vector.at(0));

	int obs_head_x = obs_node.get_x_centre();
	int obs_head_y = obs_node.get_y_centre();

	if (auto_ride_count >= max_auto_ride_count) {
		if (snake_head_dir == snake_utils::direction_e::LEFT) {
			game_utils::choose_dir(snake_utils::direction_e::UP, snake_utils::direction_e::DOWN, obs_head_x, snake_head_x, snake_head_y, obs_head_y);
		} else if (snake_head_dir == snake_utils::direction_e::RIGHT) {
			game_utils::choose_dir(snake_utils::direction_e::UP, snake_utils::direction_e::DOWN, snake_head_x, obs_head_x, snake_head_y, obs_head_y);
		} else if (snake_head_dir == snake_utils::direction_e::UP) {
			game_utils::choose_dir(snake_utils::direction_e::RIGHT, snake_utils::direction_e::LEFT, snake_head_y, obs_head_y, snake_head_x, obs_head_x);
		} else if (snake_head_dir == snake_utils::direction_e::DOWN) {
			game_utils::choose_dir(snake_utils::direction_e::RIGHT, snake_utils::direction_e::LEFT, obs_head_y, snake_head_y, snake_head_x, obs_head_x);
		}

		auto_ride_count = 0;

	} else {
		auto_ride_count++;
	}

	game_utils::check_snake_collision(snake_head_dir);

	#ifdef HARD_WALL
	bool hard_wall = snake_settings.get_hard_wall_flag();

	if (hard_wall == true) {
		game_utils::check_wall_collision(snake_head_dir);
	}
	#endif // HARD_WALL

//std::cout << "snake " << snake_head_dir << " curr_dir " << game_utils::head_dir << std::endl;
	ASSERT(auto_ride_count <= max_auto_ride_count);

}

#ifdef HARD_WALL
void game_utils::check_wall_collision(snake_utils::direction_e snake_head_dir) {

	double win_width_dle = glutGet(GLUT_WINDOW_WIDTH);
	int win_width = (int) win_width_dle;

	double win_height_dle = glutGet(GLUT_WINDOW_HEIGHT);
	int win_height = (int) win_height_dle;

	snake_utils::direction_e curr_dir(game_utils::head_dir);

	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));

	int snake_head_x = 0;
	int snake_head_x_min = 0;
	int snake_head_x_max = 0;
	int snake_head_y = 0;
	int snake_head_y_min = 0;
	int snake_head_y_max = 0;

	game_utils::get_boundaries<snake_unit::SnakeUnit>(snake_head, snake_head_x, snake_head_x_min, snake_head_x_max, snake_head_y, snake_head_y_min, snake_head_y_max);

	int speed = snake_settings.get_speed();

	bool crossing = false;

	// Check if next step will lead to crash
	if (curr_dir == snake_utils::direction_e::LEFT) {
		crossing = game_utils::wall_crossing(snake_head_x_min, 0, speed, true);
	} else if (curr_dir == snake_utils::direction_e::RIGHT) {
		crossing = game_utils::wall_crossing(snake_head_x_max, win_width, speed, false);
	} else if (curr_dir == snake_utils::direction_e::UP) {
		crossing = game_utils::wall_crossing(snake_head_y_max, win_height, speed, false);
	} else if (curr_dir == snake_utils::direction_e::DOWN) {
		crossing = game_utils::wall_crossing(snake_head_y_min, 0, speed, true);
	}

std::cout << "Wall crossing " << crossing << " curr_dir " << curr_dir << " snake_head_dir " << snake_head_dir << std::endl;
std::cout << "X min " << snake_head_x_min << " max " << snake_head_x_max << " centre " << snake_head_x <<  " Y min " << snake_head_y_min << " max " << snake_head_y_max << " centre " << snake_head_y << std::endl;

	if (crossing == true) {
		std::vector<snake_utils::direction_e> snake_dir_list;
		int snake_unit_left_dist = game_utils::dist_init_val;
		int snake_unit_right_dist = game_utils::dist_init_val;
		int snake_unit_up_dist = game_utils::dist_init_val;
		int snake_unit_down_dist = game_utils::dist_init_val;

		game_utils::populate_flags_snake(snake_dir_list, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);

		int obs_left_dist = game_utils::dist_init_val;
		int obs_right_dist = game_utils::dist_init_val;
		int obs_up_dist = game_utils::dist_init_val;
		int obs_down_dist = game_utils::dist_init_val;

		game_utils::populate_flags_obs(obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);

		snake_utils::direction_e dir1(snake_utils::direction_e::UNKNOWN);
		int snake_dist_dir1 = game_utils::dist_init_val;
		int obs_dist_dir1 = game_utils::dist_init_val;

		snake_utils::direction_e dir2(snake_utils::direction_e::UNKNOWN);
		int snake_dist_dir2 = game_utils::dist_init_val;
		int obs_dist_dir2 = game_utils::dist_init_val;

		// Use direction of the snake head because to avoid 180 degre turns
		if ((snake_head_dir == snake_utils::direction_e::RIGHT) || (snake_head_dir == snake_utils::direction_e::LEFT)) {
			dir1 = snake_utils::direction_e::UP;
			snake_dist_dir1 = snake_unit_up_dist;
			obs_dist_dir1 = obs_up_dist;
			dir2 = snake_utils::direction_e::DOWN;
			snake_dist_dir2 = snake_unit_down_dist;
			obs_dist_dir2 = obs_down_dist;
		} else if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
			dir1 = snake_utils::direction_e::RIGHT;
			snake_dist_dir1 = snake_unit_right_dist;
			obs_dist_dir1 = obs_right_dist;
			dir2 = snake_utils::direction_e::LEFT;
			snake_dist_dir2 = snake_unit_left_dist;
			obs_dist_dir2 = obs_left_dist;
		}

		// If changing direction, go to the opposite direction as the previous step
		if (snake_head_dir != curr_dir) {
			if (curr_dir == dir1) {
				game_utils::head_dir = dir2;
			} else if (curr_dir == dir2) {
				game_utils::head_dir = dir1;
			}
		} else {
			std::vector<snake_utils::direction_e> dirs = game_utils::populate_dirs(snake_dir_list);
			game_utils::set_dir_no_collision(dir1, snake_dist_dir1, obs_dist_dir1, dir2, snake_dist_dir2, obs_dist_dir2, dirs, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);
		}

std::cout << " Change dir to " << game_utils::head_dir << std::endl;
	}
}

bool game_utils::wall_crossing(int coord_obj, int reference, int speed, bool min) {
	bool crossing = false;
	if (min == true) {
		// If it is a minimum, ensure that the updated coordinate is larger than the reference
		int upd_coord = coord_obj - speed;
		crossing = (upd_coord <= reference);
	} else {
		// If it is a maximum, ensure that the updated coordinate is smaller than the reference
		int upd_coord = coord_obj + speed;
		crossing = (upd_coord >= reference);
	}

//	std::cout << "coord_obj " << coord_obj << " speed " << speed << " reference " << reference << " min? " << min << std::endl;

	return crossing;
}
#endif // HARD_WALL

void game_utils::choose_dir(snake_utils::direction_e dir1, snake_utils::direction_e dir2, int dir_coord_small, int dir_coord_big, int other_coord_small, int other_coord_big) {

	if (dir_coord_big < dir_coord_small) {
		if (other_coord_small < other_coord_big) {
			game_utils::head_dir = dir1;
		} else {
			// In case other_coord_small = other_coord_big, the direction is don't care
			game_utils::head_dir = dir2;
		}
	}

	LOG_INFO(logging::verb_level_e::DEBUG,"[Choose Direction] New direction: ", game_utils::head_dir);

}

void game_utils::check_snake_collision(snake_utils::direction_e snake_head_dir) {

	std::vector<snake_utils::direction_e> snake_dir_list;
	int snake_unit_left_dist = game_utils::dist_init_val;
	int snake_unit_right_dist = game_utils::dist_init_val;
	int snake_unit_up_dist = game_utils::dist_init_val;
	int snake_unit_down_dist = game_utils::dist_init_val;

	game_utils::populate_flags_snake(snake_dir_list, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);

	int obs_left_dist = game_utils::dist_init_val;
	int obs_right_dist = game_utils::dist_init_val;
	int obs_up_dist = game_utils::dist_init_val;
	int obs_down_dist = game_utils::dist_init_val;

	game_utils::populate_flags_obs(obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);

	std::vector<snake_utils::direction_e> dirs(game_utils::populate_dirs(snake_dir_list));

	snake_utils::direction_e curr_dir(game_utils::head_dir);

	bool collision_risk_new_dir = game_utils::unit_in_trajectory(curr_dir, dirs, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);
	bool collision_risk_old_dir = game_utils::unit_in_trajectory(snake_head_dir, dirs, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);

//	std::cout << "Game_head_dir " << curr_dir << " ditances left:" << snake_unit_left_dist << " right: " << snake_unit_right_dist << " up: " << snake_unit_up_dist << " down: " << snake_unit_down_dist << " collision_risk " << collision_risk << std::endl;
//	std::cout << "Obstacle ditances left:" << obs_left_dist << " right: " << obs_right_dist << " up: " << obs_up_dist << " down: " << obs_down_dist << std::endl;

	// If there is risk of collision in the new direction
	if (collision_risk_new_dir == true) {
		// If there is risk of collision in the old direction
		if (collision_risk_old_dir == true) {
			snake_utils::direction_e dir1(snake_utils::direction_e::UNKNOWN);
			int snake_dist_dir1 = game_utils::dist_init_val;
			int obs_dist_dir1 = game_utils::dist_init_val;

			snake_utils::direction_e dir2(snake_utils::direction_e::UNKNOWN);
			int snake_dist_dir2 = game_utils::dist_init_val;
			int obs_dist_dir2 = game_utils::dist_init_val;

			// Use direction of the snake head because to avoid 180 degre turns
			if ((snake_head_dir == snake_utils::direction_e::RIGHT) || (snake_head_dir == snake_utils::direction_e::LEFT)) {
				dir1 = snake_utils::direction_e::UP;
				snake_dist_dir1 = snake_unit_up_dist;
				obs_dist_dir1 = obs_up_dist;
				dir2 = snake_utils::direction_e::DOWN;
				snake_dist_dir2 = snake_unit_down_dist;
				obs_dist_dir2 = obs_down_dist;
			} else if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
				dir1 = snake_utils::direction_e::RIGHT;
				snake_dist_dir1 = snake_unit_right_dist;
				obs_dist_dir1 = obs_right_dist;
				dir2 = snake_utils::direction_e::LEFT;
				snake_dist_dir2 = snake_unit_left_dist;
				obs_dist_dir2 = obs_left_dist;
			}
			ASSERT(dir1 != snake_utils::direction_e::UNKNOWN);
			ASSERT(dir2 != snake_utils::direction_e::UNKNOWN);

			game_utils::set_dir_no_collision(dir1, snake_dist_dir1, obs_dist_dir1, dir2, snake_dist_dir2, obs_dist_dir2, dirs, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);
		} else {
			// If there is no risk of collision in the old direction and there is risk of collision in the new direction, then do not change direction
			game_utils::head_dir = snake_head_dir;
		}
	}

}

std::vector<snake_utils::direction_e> game_utils::populate_dirs(std::vector<snake_utils::direction_e> dir_list) {
	std::vector<snake_utils::direction_e> dirs;
	int dir_list_size = dir_list.size();

	for (int dir_no = 0; dir_no < game_utils::num_useful_dirs; dir_no++) {
		snake_utils::direction_e dir(snake_utils::direction_e::UNKNOWN);
		if (dir_no < dir_list_size) {
			dir = dir_list.at(dir_no);
		} else {
			dir = snake_utils::direction_e::UNKNOWN;
		}
		dirs.insert(dirs.end(), dir);
	}

	return dirs;
}

void game_utils::set_dir_no_collision(snake_utils::direction_e dir1, int snake_dist_dir1, int obs_dist_dir1, snake_utils::direction_e dir2, int snake_dist_dir2, int obs_dist_dir2, std::vector<snake_utils::direction_e> dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist) {

		bool collision_risk_dir1 = game_utils::unit_in_trajectory(dir1, dirs, snake_left_dist, snake_right_dist, snake_up_dist, snake_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);
		bool collision_risk_dir2 = game_utils::unit_in_trajectory(dir2, dirs, snake_left_dist, snake_right_dist, snake_up_dist, snake_down_dist, obs_left_dist, obs_right_dist, obs_up_dist, obs_down_dist);

		bool opposite_dirs = (((dirs.at(0) == snake_utils::direction_e::RIGHT) && (dirs.at(2) == snake_utils::direction_e::LEFT)) || ((dirs.at(0) == snake_utils::direction_e::LEFT) && (dirs.at(2) == snake_utils::direction_e::RIGHT)) || ((dirs.at(0) == snake_utils::direction_e::DOWN) && (dirs.at(2) == snake_utils::direction_e::UP)) || ((dirs.at(0) == snake_utils::direction_e::UP) && (dirs.at(2) == snake_utils::direction_e::DOWN)));

		// direction is valid if
		// - snake unit are not going in the opposite direction (1st and 3rd direction are nto opposite)
		// - opposite direction is not the second direction of snake units
		// - distance between snake units on a side is the minimum to force a change in direction and no obstacle is in the middle
		bool dir1_valid = (((snake_dist_dir1 == game_utils::min_dist_force_change_dir) && (((snake_dist_dir1 < obs_dist_dir1) && (obs_dist_dir1 != game_utils::dist_init_val)) || (obs_dist_dir1 == game_utils::dist_init_val))) || (dir2 != dirs.at(1)) || (opposite_dirs == false));
		bool dir2_valid = (((snake_dist_dir2 == game_utils::min_dist_force_change_dir) && (((snake_dist_dir2 < obs_dist_dir2) && (obs_dist_dir2 != game_utils::dist_init_val)) || (obs_dist_dir1 == game_utils::dist_init_val))) || (dir1 != dirs.at(1)) || (opposite_dirs == false));

		std::cout << "Snake ditances left:" << snake_left_dist << " right: " << snake_right_dist << " up: " << snake_up_dist << " down: " << snake_down_dist << std::endl;
		std::cout << "Obstacle ditances left:" << obs_left_dist << " right: " << obs_right_dist << " up: " << obs_up_dist << " down: " << obs_down_dist << std::endl;
		std::cout << "dir1_valid (" << dir1 << ") " << dir1_valid << " dir2_valid (" << dir2 << ") " << dir2_valid << " opposite_dirs " << opposite_dirs << " collision dir1." << collision_risk_dir1 << " dir2." << collision_risk_dir2 << std::endl;

		// Assert that distance on direction1 and distance on direction2 are not 1 at the same time
		ASSERT((snake_dist_dir1 != 1) || (snake_dist_dir2 != 1));

		// if no risk of collision or risk of collision on direction2 and distance measured in direction1 is larger than the one on direction2
		if ((dir1_valid == true) && ((collision_risk_dir1 == false) || ((collision_risk_dir2 == true) && (snake_dist_dir1 >= snake_dist_dir2)))) {
			game_utils::head_dir = dir1;
		} else if ((dir2_valid == true) && ((collision_risk_dir2 == false) || ((collision_risk_dir1 == true) && (snake_dist_dir2 >= snake_dist_dir1)))) {
			game_utils::head_dir = dir2;
		} else {
			LOG_ERROR("Unable to find a direction with no collision risk. Direction 1: ", dir1, " direction 2: ", dir2);
		}
}

bool game_utils::unit_in_trajectory(snake_utils::direction_e dir, std::vector<snake_utils::direction_e> dirs, int snake_left_dist, int snake_right_dist, int snake_up_dist, int snake_down_dist, int obs_left_dist, int obs_right_dist, int obs_up_dist, int obs_down_dist) {

	int snake_dist = 0;
	int obs_dist = 0;
	snake_utils::direction_e opposite_dir(snake_utils::direction_e::UNKNOWN);

	bool unit_opposite_dirs = (((dirs.at(0) == snake_utils::direction_e::RIGHT) && (dirs.at(2) == snake_utils::direction_e::LEFT)) || ((dirs.at(0) == snake_utils::direction_e::LEFT) && (dirs.at(2) == snake_utils::direction_e::RIGHT)) || ((dirs.at(0) == snake_utils::direction_e::DOWN) && (dirs.at(2) == snake_utils::direction_e::UP)) || ((dirs.at(0) == snake_utils::direction_e::UP) && (dirs.at(2) == snake_utils::direction_e::DOWN)));

	switch (dir) {
		case snake_utils::direction_e::RIGHT:
			opposite_dir = snake_utils::direction_e::LEFT;
			snake_dist = snake_right_dist;
			obs_dist = obs_right_dist;
			break;
		case snake_utils::direction_e::LEFT:
			opposite_dir = snake_utils::direction_e::RIGHT;
			snake_dist = snake_left_dist;
			obs_dist = obs_left_dist;
			break;
		case snake_utils::direction_e::UP:
			opposite_dir = snake_utils::direction_e::DOWN;
			snake_dist = snake_up_dist;
			obs_dist = obs_up_dist;
			break;
		case snake_utils::direction_e::DOWN:
			opposite_dir = snake_utils::direction_e::UP;
			snake_dist = snake_down_dist;
			obs_dist = obs_down_dist;
			break;
		default:
			LOG_ERROR("Unknown direction");
			break;
	}

	bool dist_collision = (snake_dist <= game_utils::min_dist_force_change_dir);
	bool heading_collision = ((opposite_dir == dirs.at(1)) && (unit_opposite_dirs == true));
	bool collision_risk = ((heading_collision || dist_collision) && (snake_dist != game_utils::dist_init_val) && (((obs_dist != game_utils::dist_init_val) && (snake_dist < obs_dist)) || (obs_dist == game_utils::dist_init_val)));

	return collision_risk;

}

void game_utils::populate_flags_snake(std::vector<snake_utils::direction_e> & dir_list, int & left_dist, int & right_dist, int & up_dist, int & down_dist) {
	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));

	snake_utils::direction_e prev_dir(snake_head.get_direction());
	snake_utils::direction_e curr_dir(snake_head.get_direction());

	dir_list.push_back(curr_dir);

	int snake_head_x = 0;
	int snake_head_width = snake_head.get_width();
	int snake_head_x_min = 0;
	int snake_head_x_max = 0;
	int snake_head_y = 0;
	int snake_head_height = snake_head.get_height();
	int snake_head_y_min = 0;
	int snake_head_y_max = 0;

	game_utils::get_boundaries<snake_unit::SnakeUnit>(snake_head, snake_head_x, snake_head_x_min, snake_head_x_max, snake_head_y, snake_head_y_min, snake_head_y_max);

	#ifdef HARD_WALL
	bool hard_wall = snake_settings.get_hard_wall_flag();

	if (hard_wall == true) {
		// Initialize distances with snake head coordinates if hard wall is on
		double win_width_dle = glutGet(GLUT_WINDOW_WIDTH);
		int win_width = (int) win_width_dle;

		double win_height_dle = glutGet(GLUT_WINDOW_HEIGHT);
		int win_height = (int) win_height_dle;

		game_utils::update_win_dist(win_height, snake_head_y, snake_head_height, down_dist, up_dist);
		game_utils::update_win_dist(win_width, snake_head_x, snake_head_width, left_dist, right_dist);
	}
	#endif // HARD_WALL

	if (snake_vector.size() > 1) {
		for(std::vector<snake_unit::SnakeUnit>::iterator unit = (snake_vector.begin()+1); unit != snake_vector.end(); ++unit) {

			int snake_unit_x = 0;
			int snake_unit_width = unit->get_width();
			int snake_unit_x_min = 0;
			int snake_unit_x_max = 0;
			int snake_unit_y = 0;
			int snake_unit_height = unit->get_height();
			int snake_unit_y_min = 0;
			int snake_unit_y_max = 0;

			game_utils::get_boundaries<snake_unit::SnakeUnit>(*unit, snake_unit_x, snake_unit_x_min, snake_unit_x_max, snake_unit_y, snake_unit_y_min, snake_unit_y_max);

			int avg_height = (snake_unit_height + snake_head_height)/2;
			int avg_width  = (snake_unit_width + snake_head_width)/2;

			if (
				// head and unit are aligned on the X axis
				game_utils::coord_overlap(snake_head_x_min, snake_head_x_max, snake_unit_x_min, snake_unit_x_max) == true
			) {
				LOG_INFO(logging::verb_level_e::DEBUG,"[Populate Flags] Y coordinates: Snake Head.", snake_head_y, ", Snake Unit.", snake_unit_y, " Distance: Up.", up_dist, " Down.", down_dist);
				game_utils::update_dist(snake_head_y, snake_unit_y, avg_height, down_dist, up_dist);
	//std::cout << "X axis alignment Snake." << snake_head_y << ", Unit."<< snake_unit_y <<" Distance: Up." << up_dist<< " Down."<< down_dist << std::endl;
			} else if (
				// head and unit are aligned on the Y axis
				game_utils::coord_overlap(snake_head_y_min, snake_head_y_max, snake_unit_y_min, snake_unit_y_max) == true
			) {
				LOG_INFO(logging::verb_level_e::DEBUG,"[Populate Flags] X coordinates: Snake Head.", snake_head_x, ", Snake Unit.", snake_unit_x, ", Distance: Left.", left_dist, " Right.", right_dist);
				game_utils::update_dist(snake_head_x, snake_unit_x, avg_width, left_dist, right_dist);
	//std::cout << "Y axis alignment Snake." << snake_head_x << ", Unit."<< snake_unit_x <<" Distance: left." << left_dist<< " right."<< right_dist << std::endl;
			}

			curr_dir = unit->get_direction();
			if (curr_dir != prev_dir) {
				dir_list.push_back(curr_dir);
			}

			prev_dir = curr_dir;

		}
	}

}

void game_utils::populate_flags_obs(int & left_dist, int & right_dist, int & up_dist, int & down_dist) {
	std::vector<obstacle::Obstacle> & obs_vector(game_utils::obstacles.get_vector());
	std::vector<snake_unit::SnakeUnit> & snake_vector(game_utils::snake.get_vector());
	snake_unit::SnakeUnit snake_head(snake_vector.at(0));

	int snake_head_x = snake_head.get_x_centre();
	int snake_head_width = snake_head.get_width();
	int snake_head_y = snake_head.get_y_centre();
	int snake_head_height = snake_head.get_height();

	#ifdef HARD_WALL
	bool hard_wall = snake_settings.get_hard_wall_flag();

	if (hard_wall == true) {
		// Initialize distances with snake head coordinates if hard wall is on
		double win_width_dle = glutGet(GLUT_WINDOW_WIDTH);
		int win_width = (int) win_width_dle;

		double win_height_dle = glutGet(GLUT_WINDOW_HEIGHT);
		int win_height = (int) win_height_dle;

		game_utils::update_win_dist(win_height, snake_head_y, snake_head_height, down_dist, up_dist);
		game_utils::update_win_dist(win_width, snake_head_x, snake_head_width, left_dist, right_dist);
	}
	#endif // HARD_WALL

	for (auto curr_node : obs_vector) {

		int obs_head_x = curr_node.get_x_centre();
		int obs_head_width = curr_node.get_width();
		int obs_head_y = curr_node.get_y_centre();
		int obs_head_height = curr_node.get_height();
		int avg_height = (obs_head_height + snake_head_height)/2;
		int avg_width  = (obs_head_width + snake_head_width)/2;

		game_utils::update_dist(snake_head_y, obs_head_y, avg_height, down_dist, up_dist);
		game_utils::update_dist(snake_head_x, obs_head_x, avg_width, left_dist, right_dist);

	}
}



template <typename ptr_t>
void game_utils::get_boundaries(ptr_t ptr, int & x_centre, int & x_min, int & x_max, int & y_centre, int & y_min, int & y_max) {

	x_centre = ptr.get_x_centre();
	int width = ptr.get_width();
	game_utils::get_coord_range(x_centre, width, x_min, x_max);
	y_centre = ptr.get_y_centre();
	int height = ptr.get_height();
	game_utils::get_coord_range(y_centre, height, y_min, y_max);

//std::cout << "X min " << x_min << " max " << x_max << " centre " << x_centre <<  " Y min " << y_min << " max " << y_max << " centre " << y_centre << std::endl;
}

void game_utils::get_coord_range(int centre, int dim, int & min_coord, int & max_coord) {
	min_coord = centre - dim/2;
	max_coord = centre + dim/2;
}

bool game_utils::coord_overlap(int coord1_min, int coord1_max, int coord2_min, int coord2_max) {
//std::cout << "Coord1: min " << coord1_min << " max " << coord1_max << " Coord2: min " << coord2_min << " max " << coord2_max << std::endl;
	LOG_INFO(logging::verb_level_e::DEBUG,"[Coordinate Overlap] Coordinate1: minimum->", coord1_min, ", maximum->", coord1_max, " Coordinate2: minimum->", coord2_min, ", maximum->", coord2_max);
	bool overlap = ((coord1_min >= coord2_min) && (coord1_min < coord2_max)) || ((coord1_max > coord2_min) && (coord1_max <= coord2_max));
	return overlap;
}

#ifdef HARD_WALL
void game_utils::update_win_dist(int win_coord, int obj_coord, int dim, int & dist_close, int & dist_far) {
	int abs_dist_far = abs(win_coord - obj_coord);
	float dist_norm_far = ((float)abs_dist_far)/((float)dim);
	int dist_norm_ceil_far = (int) ceil(dist_norm_far);

	if ((dist_far == game_utils::dist_init_val) || (dist_far > dist_norm_ceil_far)) {
		dist_far = dist_norm_ceil_far;
	}

	int abs_dist_close = abs(obj_coord);
	float dist_norm_close = ((float)abs_dist_close)/((float)dim);
	int dist_norm_ceil_close = (int) ceil(dist_norm_close);

	if ((dist_close == game_utils::dist_init_val) || (dist_close > dist_norm_ceil_close)) {
		dist_close = dist_norm_ceil_close;
	}
}
#endif // HARD_WALL

void game_utils::update_dist(int coord1, int coord2, int avg_dim, int & dist_1l2, int & dist_1s2) {
	int abs_dist = abs(coord1 - coord2);
	float dist_norm = ((float)abs_dist)/((float)avg_dim);
	int dist_norm_ceil = (int) ceil(dist_norm);

	LOG_INFO(logging::verb_level_e::DEBUG,"[Update Distance] Coordinate1->", coord1, " Coordinate2->", coord2, " Distance: 1l2->", dist_1l2, " 1s2->", dist_1s2, " Current->", dist_norm_ceil);
	if (coord1 >= coord2) {
		if ((dist_1l2 == game_utils::dist_init_val) || (dist_1l2 > dist_norm_ceil)) {
			dist_1l2 = dist_norm_ceil;
		}
	} else {
		if ((dist_1s2 == game_utils::dist_init_val) || (dist_1s2 > dist_norm_ceil)) {
			dist_1s2 = dist_norm_ceil;
		}
	}
}

void game_utils::set_head_dir(snake_utils::direction_e dir) {
	game_utils::head_dir = dir;
}

snake_utils::direction_e game_utils::get_head_dir() {
	return game_utils::head_dir;
}
