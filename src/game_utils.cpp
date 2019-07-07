/**
 * @copyright
 * @file game_utils.cpp
 * @author Andrea Gianarda
 * @date 10th June 2019
 * @brief Game utils functions
 */

#include <iostream>
#include <cmath>

#include "settings.h"
#include "utility.h"
#include "logging.h"
#include "colours.h"
#include "game_utils.h"
#include "graphics_utils.h"
#include "snake_list.h"
#include "snake_node.h"
#include "snake_utils.h"
#include "snake_direction_list.h"

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
		static snake_list::SnakeList * snake;

		/**
		 * @brief pointer to snake elements
		 *
		 */
		static obstacle_list::ObstacleList * obstacles;

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
	}
}
/** @} */ // End of addtogroup GameUtilsGroup

void game_utils::init_snake_list() {
	std::string type("Snake");
	game_utils::snake = new snake_list::SnakeList(type);
	if (game_utils::snake == nullptr) {
		LOG_ERROR("Can't allocate memory for snake list ", type, ".");
	}
}

void game_utils::init_obstacle_list() {
	std::string type("Obstacle");
	game_utils::obstacles = new obstacle_list::ObstacleList(type);
	if (game_utils::obstacles == nullptr) {
		LOG_ERROR("Can't allocate memory for obstacle list ", type, ".");
	}
}

snake_list::SnakeList * & game_utils::get_snake_ptr() {
	return game_utils::snake;
}

obstacle_list::ObstacleList * & game_utils::get_obstacle_ptr() {
	return game_utils::obstacles;
}

void game_utils::populate_snake_list() {
	int centre_x = snake_settings.get_head_centre_x();
	int centre_y = snake_settings.get_head_centre_y();

	int snake_units = snake_settings.get_snake_units();
	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	snake_utils::direction_e snake_head_dir = snake_settings.get_head_dir();
	colours::palette_e colour = snake_settings.get_snake_colour();

	for (int unit_no=0; unit_no < snake_units; unit_no++) {

		game_utils::add_snake_node(centre_x, centre_y, node_width, node_height, snake_head_dir, colour);
		//game_utils::snake->add_node(centre_x, centre_y, game_utils::node_width, game_utils::node_height, game_utils::init_head_dir, (colours::palette_e) unit_no);
		centre_x += node_width;
		//game_utils::snake->add_node(centre_x, centre_y, game_utils::node_width, game_utils::node_height, game_utils::init_head_dir, colours::palette_e::RED);
		//centre_y += game_utils::node_height;

	}

	// Colour snake_head differently to ease debug
	snake_node::SnakeNode * snake_head = game_utils::snake->get_head();
	snake_head->set_colour(colours::palette_e::YELLOW);

}

void game_utils::set_snake_settings() {

	snake_node::SnakeNode * snake_head = game_utils::snake->get_head();
	snake_utils::direction_e snake_head_dir = snake_head->get_direction();
	snake_settings.set_head_dir(snake_head_dir);
	int snake_head_x = snake_head->get_x_centre();
	snake_settings.set_head_centre_x(snake_head_x);
	int snake_head_y = snake_head->get_y_centre();
	snake_settings.set_head_centre_y(snake_head_y);

}

void game_utils::add_snake_node (int centre_x, int centre_y, int node_width, int node_height, snake_utils::direction_e dir, colours::palette_e colour) {
	game_utils::snake->add_node(centre_x, centre_y, node_width, node_height, dir, colour);
}

void game_utils::add_obs_node (int centre_x, int centre_y, int node_width, int node_height, colours::palette_e colour) {
	game_utils::obstacles->add_node(centre_x, centre_y, node_width, node_height, colour);
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
	snake_node::SnakeNode * snake_head = game_utils::snake->get_head();
	int snake_head_x = snake_head->get_x_centre();
	int snake_head_width = snake_head->get_width();
	int snake_head_x_min = snake_head_x - snake_head_width/2;
	int snake_head_x_max = snake_head_x + snake_head_width/2;
	int snake_head_y = snake_head->get_y_centre();
	int snake_head_height = snake_head->get_height();
	int snake_head_y_min = snake_head_y - snake_head_height/2;
	int snake_head_y_max = snake_head_y + snake_head_height/2;

	// obstacle pointer
	obstacle::ObstacleNode * curr_node = game_utils::obstacles->get_head();

	bool contact = false;

	while (curr_node != nullptr) {
		int obs_x = curr_node->get_x_centre();
		int obs_width = curr_node->get_width();
		int obs_x_min = obs_x - obs_width/2;
		int obs_x_max = obs_x + obs_width/2;
		int obs_y = curr_node->get_y_centre();
		int obs_height = curr_node->get_height();
		int obs_y_min = obs_y - obs_height/2;
		int obs_y_max = obs_y + obs_height/2;

		// Save temporary obstacle
		obstacle::ObstacleNode * node_tmp = curr_node;
		curr_node = curr_node->get_next();

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
			game_utils::obstacles->remove_node(node_tmp);
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
	colours::palette_e colour = snake_settings.get_obs_colour();

	// Random coordinates must be within node_width/2 and (win_width-node_width/2)
	int centre_x = (rand() % (win_width_int - node_width)) + node_width/2;

	// Random coordinates must be within node_height/2 and (win_height-node_height/2)
	int centre_y = (rand() % (win_height_int - node_height)) + node_height/2;

	//game_utils::obstacles->add_node(centre_x, centre_y, game_utils::node_width, game_utils::node_height, colours::palette_e::PURPLE);
	game_utils::add_obs_node(centre_x, centre_y, node_width, node_height, colour);
}

void game_utils::free_obstacle_list() {
	game_utils::obstacles->~ObstacleList();
	delete game_utils::obstacles;
}

void game_utils::free_snake_list() {
	game_utils::snake->~SnakeList();
	delete game_utils::snake;
}

void game_utils::free_window_list() {
	graphics_utils::delete_all_windows();
}

void game_utils::save_game(std::string filename) {
	// obstacle pointer
	snake_node::SnakeNode * curr_snake_node = game_utils::snake->get_head();

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

	while (curr_snake_node != nullptr) {
		save.write_ofile("//******************************\n");
		save.write_ofile("// Snake Node ", snake_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		curr_snake_node->save_data(save);

		save.write_ofile("\n");

		// Save temporary obstacle
		curr_snake_node = curr_snake_node->get_next();
		snake_node_cnt++;
	}

	ASSERT(snake_node_cnt==snake_units);

	// obstacle pointer
	obstacle::ObstacleNode * curr_obs_node = game_utils::obstacles->get_head();

	int obs_node_cnt = 0;

	while (curr_obs_node != nullptr) {

		save.write_ofile("//******************************\n");
		save.write_ofile("// Obstacle Node ", obs_node_cnt, "\n");
		save.write_ofile("//******************************\n");

		// Save temporary obstacle
		curr_obs_node->save_data(save);

		curr_obs_node = curr_obs_node->get_next();
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

	snake_node::SnakeNode * snake_head = game_utils::snake->get_head();
	snake_utils::direction_e snake_head_dir = snake_head->get_direction();

	// Coordinates
	int snake_head_x = snake_head->get_x_centre();
	int snake_head_y = snake_head->get_y_centre();

	// Dimensions
	int height = snake_head->get_height();
	int width = snake_head->get_width();

	int speed = snake_settings.get_speed();

	int max_auto_ride_count = 0;

	if ((snake_head_dir == snake_utils::direction_e::LEFT) || (snake_head_dir == snake_utils::direction_e::RIGHT)) {
		float result = ((float)width)/((float)speed);
		max_auto_ride_count = (int) floor(result);
	} else if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
		float result = ((float)height)/((float)speed);
		max_auto_ride_count = (int) floor(result);
	}

	obstacle::ObstacleNode * obs_head = game_utils::obstacles->get_head();

	int obs_head_x = obs_head->get_x_centre();
	int obs_head_y = obs_head->get_y_centre();

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
		game_utils::check_dir(snake_head_dir);
	} else {
		auto_ride_count++;
	}

	ASSERT(auto_ride_count <= max_auto_ride_count);

}

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

void game_utils::check_dir(snake_utils::direction_e snake_head_dir) {

	snake_direction_list::SnakeDirectionList * snake_dir_list = new snake_direction_list::SnakeDirectionList();
	int snake_unit_left_dist = game_utils::dist_init_val;
	int snake_unit_right_dist = game_utils::dist_init_val;
	int snake_unit_up_dist = game_utils::dist_init_val;
	int snake_unit_down_dist = game_utils::dist_init_val;

	game_utils::populate_flags(snake_dir_list, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);

	bool collision_risk = game_utils::unit_in_trajectory(game_utils::head_dir, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);

	cout << "Head dir " << snake_head_dir << " ditances left:" << snake_unit_left_dist << " right: " << snake_unit_right_dist << " up: " << snake_unit_up_dist << " down: " << snake_unit_down_dist << " collision_risk " << collision_risk << endl;

	snake_utils::direction_e dir1 = snake_utils::direction_e::UNKNOWN;
	int dist_dir1 = game_utils::dist_init_val;

	snake_utils::direction_e dir2 = snake_utils::direction_e::UNKNOWN;
	int dist_dir2 = game_utils::dist_init_val;

	if (collision_risk == true) {
		if ((snake_head_dir == snake_utils::direction_e::RIGHT) || (snake_head_dir == snake_utils::direction_e::LEFT)) {
			dir1 = snake_utils::direction_e::UP;
			dist_dir1 = snake_unit_up_dist;
			dir2 = snake_utils::direction_e::DOWN;
			dist_dir2 = snake_unit_down_dist;
		} else if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
			dir1 = snake_utils::direction_e::RIGHT;
			dist_dir1 = snake_unit_right_dist;
			dir2 = snake_utils::direction_e::LEFT;
			dist_dir2 = snake_unit_left_dist;
		}
		ASSERT(dir1 != snake_utils::direction_e::UNKNOWN);
		ASSERT(dir2 != snake_utils::direction_e::UNKNOWN);

		bool collision_risk_dir1 = game_utils::unit_in_trajectory(dir1, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);
		bool collision_risk_dir2 = game_utils::unit_in_trajectory(dir2, snake_unit_left_dist, snake_unit_right_dist, snake_unit_up_dist, snake_unit_down_dist);

		// Assert that distance on direction1 and distance on direction2 are not 1 at the same time
		ASSERT((dist_dir1 != 1) || (dist_dir2 != 1));

		// if no risk of collision or risk of collision on direction2 and distance measured in direction1 is larger than the one on direction2
		if ((collision_risk_dir1 == false) || ((collision_risk_dir2 == true) && (dist_dir1 >= dist_dir2))) {
			game_utils::head_dir = dir1;
		} else if ((collision_risk_dir2 == false) || ((collision_risk_dir1 == true) && (dist_dir2 >= dist_dir1))) {
			game_utils::head_dir = dir2;
		} else {
			LOG_ERROR("Unable to find a direction with no collision risk. Current direction: ", snake_head_dir, " direction 1: ", dir1, " direction 2: ", dir2);
		}
	}
}

bool game_utils::unit_in_trajectory(snake_utils::direction_e dir, int left_dist, int right_dist, int up_dist, int down_dist) {

	bool collision_risk = false;

	switch (dir) {
		case snake_utils::direction_e::RIGHT:
			collision_risk = ((right_dist <= game_utils::min_dist_force_change_dir) && (right_dist != game_utils::dist_init_val));
			break;
		case snake_utils::direction_e::LEFT:
			collision_risk = ((left_dist <= game_utils::min_dist_force_change_dir) && (left_dist != game_utils::dist_init_val));
			break;
		case snake_utils::direction_e::UP:
			collision_risk = ((up_dist <= game_utils::min_dist_force_change_dir) && (up_dist != game_utils::dist_init_val));
			break;
		case snake_utils::direction_e::DOWN:
			collision_risk = ((down_dist <= game_utils::min_dist_force_change_dir) && (down_dist != game_utils::dist_init_val));
			break;
		default:
			LOG_ERROR("Unknown direction");
			break;
	}

	return collision_risk;

}

void game_utils::populate_flags(snake_direction_list::SnakeDirectionList * & dir_list, int & left_dist, int & right_dist, int & up_dist, int & down_dist) {
	snake_node::SnakeNode * snake_head = game_utils::snake->get_head();

	snake_utils::direction_e prev_dir = snake_head->get_direction();
	snake_utils::direction_e curr_dir = snake_head->get_direction();

	dir_list->add_node(curr_dir);

	int snake_head_x = snake_head->get_x_centre();
	int snake_head_width = snake_head->get_width();
	int snake_head_x_min = snake_head_x - snake_head_width/2;
	int snake_head_x_max = snake_head_x + snake_head_width/2;
	int snake_head_y = snake_head->get_y_centre();
	int snake_head_height = snake_head->get_height();
	int snake_head_y_min = snake_head_y - snake_head_height/2;
	int snake_head_y_max = snake_head_y + snake_head_height/2;

	// Move away from the head
	snake_head = snake_head->get_next();

	while (snake_head != nullptr) {

		int snake_unit_x = snake_head->get_x_centre();
		int snake_unit_width = snake_head->get_width();
		int snake_unit_x_min = snake_unit_x - snake_unit_width/2;
		int snake_unit_x_max = snake_unit_x + snake_unit_width/2;
		int snake_unit_y = snake_head->get_y_centre();
		int snake_unit_height = snake_head->get_height();
		int snake_unit_y_min = snake_unit_y - snake_unit_height/2;
		int snake_unit_y_max = snake_unit_y + snake_unit_height/2;
		int avg_height = (snake_unit_height + snake_head_height)/2;
		int avg_width  = (snake_unit_width + snake_head_width)/2;

		if (
			// head and unit are aligned on the X axis
			game_utils::coord_overlap(snake_head_x_min, snake_head_x_max, snake_unit_x_min, snake_unit_x_max) == true
		) {
			LOG_INFO(logging::verb_level_e::DEBUG,"[Populate Flags] Y coordinates: Snake Head->", snake_head_y, ", Snake Unit->", snake_unit_y, " Distance: Up->", up_dist, " Down->", down_dist);
			game_utils::update_dist(snake_head_y, snake_unit_y, avg_height, down_dist, up_dist);
cout << "X axis alignment Snake->" << snake_head_y << ", Unit->"<< snake_unit_y <<" Distance: Up->" << up_dist<< " Down->"<< down_dist << endl;
		} else if (
			// head and unit are aligned on the Y axis
			game_utils::coord_overlap(snake_head_y_min, snake_head_y_max, snake_unit_y_min, snake_unit_y_max) == true
		) {
			LOG_INFO(logging::verb_level_e::DEBUG,"[Populate Flags] X coordinates: Snake Head->", snake_head_x, ", Snake Unit->", snake_unit_x, ", Distance: Left->", left_dist, " Right->", right_dist);
			game_utils::update_dist(snake_head_x, snake_unit_x, avg_width, left_dist, right_dist);
cout << "Y axis alignment Snake->" << snake_head_x << ", Unit->"<< snake_unit_x <<" Distance: left->" << left_dist<< " right->"<< right_dist << endl;
		}

		curr_dir = snake_head->get_direction();
		if (curr_dir != prev_dir) {
			dir_list->add_node(curr_dir);
		}

		snake_head = snake_head->get_next();
		prev_dir = curr_dir;

	}

}

bool game_utils::coord_overlap(int coord1_min, int coord1_max, int coord2_min, int coord2_max) {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Coordinate Overlap] Coordinate1: minimum->", coord1_min, ", maximum->", coord1_max, " Coordinate2: minimum->", coord2_min, ", maximum->", coord2_max);
	bool overlap = ((coord1_min >= coord2_min) && (coord1_min < coord2_max)) || ((coord1_max > coord2_min) && (coord1_max <= coord2_max));
	return overlap;
}

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
