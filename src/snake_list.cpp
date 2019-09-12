/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "colours.h"
#include "settings.h"
#include "game_utils.h"
#include "basic_obj_list.h"
#include "snake_list.h"
#include "snake_unit.h"
#include "logging.h"
#include "insert_snake_unit.h"

snake_list::SnakeList::~SnakeList() {

	LOG_INFO(logging::verb_level_e::DEBUG, "Snake List Destructor");

	this->~BasicObjList();


}

// Add nodes from the head down
void snake_list::SnakeList::add_element(int centre_x, int centre_y, int snake_width, int snake_height, snake_utils::direction_e snake_direction, colours::palette_e snake_colour) {

	std::vector<snake_unit::SnakeUnit> & snake_vector (this->get_vector());
	std::string name(this->get_name());

	snake_unit::SnakeUnit new_snake(name, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour);
	LOG_INFO(logging::verb_level_e::LOW, "[Add Snake Unit] Name: ", name, new_snake, ".");

	// Check whether snake_vector is empty
	if(snake_vector.size() > 0) {
		snake_unit::SnakeUnit snake_found;
		std::vector<snake_unit::SnakeUnit>::iterator snake_prev;
		std::vector<snake_unit::SnakeUnit>::iterator snake_head_it(snake_vector.begin());
		std::vector<snake_unit::SnakeUnit>::iterator snake_tail(snake_vector.end());

		snake_unit::SnakeUnit snake_head(snake_vector.front());

		int width_head = snake_head.get_width();
		ASSERT(width_head == snake_width)

		int height_head = snake_head.get_height();
		ASSERT(height_head == snake_height)

		bool head_found = false;

		std::vector<snake_unit::SnakeUnit>::iterator element_it = std::find_if(snake_vector.begin(), snake_vector.end(), insert_snake_unit::InsertSnakeUnit<snake_utils::direction_e,snake_unit::SnakeUnit>(centre_x, centre_y, snake_direction));
		snake_prev = element_it;

		if (element_it != snake_tail) {
			int index = std::distance(snake_vector.begin(), element_it);
			if (element_it != snake_head_it) {
				head_found = false;
				snake_found = snake_vector.at(index-1);
				element_it = std::prev(element_it);
			} else {
				head_found = true;
				// Set snake_found to the last element as snake_found will be appended at the end of the list
				snake_found = snake_vector.at(index);
			}
		} else {
			head_found = false;
		}

		if (head_found == true) {
			snake_vector.insert(snake_vector.begin(), new_snake);
		} else {

			int width_found = snake_found.get_width();
			ASSERT(width_found == snake_width)

			int height_found = snake_found.get_height();
			ASSERT(height_found == snake_height)

			snake_utils::direction_e direction_found(snake_found.get_direction());

			int x_centre_found = snake_found.get_x_centre();
			int y_centre_found = snake_found.get_y_centre();

			int hdistance_units = 0;
			int hdistance_measured = 0;
			int vdistance_units = 0;
			int vdistance_measured = 0;

			if ((direction_found == snake_utils::direction_e::RIGHT) || (direction_found == snake_utils::direction_e::LEFT)) {
				hdistance_units = (snake_width/2) + (width_found/2);
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = 0;
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			} else if ((direction_found == snake_utils::direction_e::UP) || (direction_found == snake_utils::direction_e::DOWN)) {
				hdistance_units = 0;
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = (snake_height/2) + (height_found/2);
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			}

			if (direction_found == snake_direction) {
				ASSERT(hdistance_units == hdistance_measured)
				ASSERT(vdistance_units == vdistance_measured)
			} else { // If not same direction
				// Sum of distances on X and Y axis must be equal to the sum of expected distances
				ASSERT((vdistance_units + hdistance_units) == (vdistance_measured + hdistance_measured))
			}

			// Insert new snake unit
			snake_vector.insert(element_it, new_snake);
		}
	} else {
		snake_vector.insert(snake_vector.begin(), new_snake);
	}

}

void snake_list::SnakeList::move(const int & speed, const int & win_width, const int & win_height, const snake_utils::direction_e & head_dir) {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Window dimensions: Width ", win_width, " Height ", win_height, " Speed: ", speed);

	std::vector<snake_unit::SnakeUnit> & snake_vector (this->get_vector());

	snake_unit::SnakeUnit & snake_head(snake_vector.front());

	snake_utils::direction_e direction_prev(head_dir);
	int x_centre_prev = snake_head.get_x_centre();
	int y_centre_prev = snake_head.get_y_centre();
	int height_prev = snake_head.get_height();
	int width_prev = snake_head.get_width();

	snake_utils::direction_e direction_curr(snake_head.get_direction());
	int x_centre_curr = snake_head.get_x_centre();
	int y_centre_curr = snake_head.get_y_centre();
	int height_curr = snake_head.get_height();
	int width_curr = snake_head.get_width();


	snake_settings.set_head_centre_x(x_centre_curr);
	snake_settings.set_head_centre_y(y_centre_curr);
	snake_settings.set_head_dir(direction_curr);

	int speed_int = speed;

	for(std::vector<snake_unit::SnakeUnit>::iterator el = snake_vector.begin(); el != snake_vector.end(); ++el) {
		snake_unit::SnakeUnit & snake_el(*el);

		// Store values of current element before updating its position and direction
		direction_curr = snake_el.get_direction();
		x_centre_curr = snake_el.get_x_centre();
		y_centre_curr = snake_el.get_y_centre();
		height_curr = snake_el.get_height();
		width_curr = snake_el.get_width();

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Current Unit: X ", x_centre_curr, " Y ", y_centre_curr, " Direction ", direction_curr);
		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Previous Unit: X ", x_centre_prev, " Y ", y_centre_prev, " Direction ", direction_prev);

		if (direction_prev != direction_curr) {
			if (el != snake_vector.begin()) {
				int sign = 0;
				// UP
				if ((direction_prev == snake_utils::direction_e::UP) || (direction_prev == snake_utils::direction_e::RIGHT)) {
					sign = -1;
				} else {
					sign = 1;
				}

				ASSERT((sign == 1) || (sign == -1));

				int height_centre_distance = (height_curr + height_prev)/2;
				int y_diff = abs(y_centre_curr - y_centre_prev);
				int width_centre_distance = (width_curr + width_prev)/2;
				int x_diff = abs(x_centre_curr - x_centre_prev);
				if (((direction_curr == snake_utils::direction_e::RIGHT) && (direction_prev == snake_utils::direction_e::LEFT)) || ((direction_curr == snake_utils::direction_e::LEFT) && (direction_prev == snake_utils::direction_e::RIGHT))) {
					if ((y_diff < height_centre_distance) && (x_diff < width_centre_distance)) {
						LOG_ERROR("Units moving in opposite horizintal movement and colliding. Direction: previous ", direction_prev, " current ", direction_curr, " Coordinate difference: X ", x_diff, " Y ", y_diff, " centre distance: width ", width_centre_distance, " height ", height_centre_distance);
					}
				} else if (((direction_curr == snake_utils::direction_e::UP) && (direction_prev == snake_utils::direction_e::DOWN)) || ((direction_curr == snake_utils::direction_e::DOWN) && (direction_prev == snake_utils::direction_e::UP))) {
					if ((x_diff < width_centre_distance) && (y_diff < height_centre_distance)) {
						LOG_ERROR("Units moving in opposite vertical movement and colliding. Direction: previous ", direction_prev, " current ", direction_curr, " Coordinate difference: X ", x_diff, " Y ", y_diff, " centre distance: width ", width_centre_distance, " height ", height_centre_distance);
					}
				}

				// Consecutive units can't travel in opposite direction
				ASSERT(
					((direction_curr == snake_utils::direction_e::RIGHT) && (direction_prev != snake_utils::direction_e::LEFT))  ||
					((direction_curr == snake_utils::direction_e::LEFT)  && (direction_prev != snake_utils::direction_e::RIGHT)) ||
					((direction_curr == snake_utils::direction_e::UP)    && (direction_prev != snake_utils::direction_e::DOWN))  ||
					((direction_curr == snake_utils::direction_e::DOWN)  && (direction_prev != snake_utils::direction_e::UP))
				);

				// Adjust coordinate centres of pervious and current unit must be aligned as to ditance between centres is kept constant
				// Y for horizontal to vertical movement
				// X for vertical to horizontal movement
				if (((direction_curr == snake_utils::direction_e::RIGHT) || (direction_curr == snake_utils::direction_e::LEFT)) && ((int) abs(x_centre_prev - x_centre_curr) < speed)) {

					// Unit moving horizontally:
					// - X is force to aligned (set previous unit X coordinate)
					// - Y is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, win_height, height_curr, height_prev, y_centre_curr, y_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", x_centre_prev, " Y ", centre_adj);
					snake_el.set_x_centre(x_centre_prev);
					snake_el.set_y_centre(centre_adj);
				} else if (((direction_curr == snake_utils::direction_e::UP) || (direction_curr == snake_utils::direction_e::DOWN)) && ((int) abs(y_centre_prev - y_centre_curr) < speed)) {
					// Unit moving vertically:
					// - Y is force to aligned (set previous unit Y coordinate)
					// - X is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, win_width, width_curr, width_prev, x_centre_curr, x_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", centre_adj, " Y ", y_centre_prev);
					snake_el.set_x_centre(centre_adj);
					snake_el.set_y_centre(y_centre_prev);
				}
			} else {
				// If snake has more than one element
				if (el != snake_vector.end()) {
					std::vector<snake_unit::SnakeUnit>::iterator el_next(std::next(el, 1));
					snake_unit::SnakeUnit snake_el_next(*el_next);

					snake_utils::direction_e direction_next(snake_el_next.get_direction());

					// If head and second unit have the same direction, the head can change again
					if (direction_next == direction_curr) {
						snake_el.set_direction(direction_prev);
					}
				}
			}
		} else {

			int adjustment = 0;

			if ((direction_curr == snake_utils::direction_e::RIGHT) || (direction_curr == snake_utils::direction_e::LEFT)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, width_curr, width_prev, x_centre_curr, x_centre_prev, y_centre_curr, y_centre_prev, speed, snake_utils::direction_e::DOWN, snake_utils::direction_e::UP, direction_curr, win_width);
			} else if ((direction_curr == snake_utils::direction_e::UP) || (direction_curr == snake_utils::direction_e::DOWN)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, height_curr, height_prev, y_centre_curr, y_centre_prev, x_centre_curr, x_centre_prev, speed, snake_utils::direction_e::LEFT, snake_utils::direction_e::RIGHT, direction_curr, win_height);
			}

			if ((adjustment == 0) || (snake_el == snake_head)) {
				speed_int = speed;
			} else {
				if (adjustment <= speed) {
					speed_int = adjustment;
				} else {
					speed_int = 0;
				}
			}

		}

		snake_el.move(speed_int, win_width, win_height);

		// Store values of previous element before updating its position and direction
		direction_prev = direction_curr;
		x_centre_prev = x_centre_curr;
		y_centre_prev = y_centre_curr;
		height_prev = height_curr;
		width_prev = width_curr;

	}
}

int snake_list::SnakeList::change_dir(snake_unit::SnakeUnit & snake_el, int win_dim, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_utils::direction_e prev_dir) {
	// Distance between centres
	int centre_distance = ((curr_dim + prev_dim)/2);
	int curr_distance = compute_centre_distance(curr_coord_mov_dir, prev_coord_mov_dir, win_dim, centre_distance);

	// Adjustment: distance between centres - actual distance between centres 
	int adjustment = centre_distance - curr_distance;
	ASSERT((adjustment >= 0) && (adjustment <= centre_distance));

	int centre_adj = curr_coord_mov_dir + sign * adjustment;
	int adj_distance = compute_centre_distance(prev_coord_mov_dir, centre_adj, win_dim, centre_distance);

	if(adj_distance != centre_distance) {
		LOG_ERROR("Snake units are touching each other.\nUnit1 -> ", centre_adj, ". Unit2 -> ", prev_coord_mov_dir);
	}

	ASSERT(adj_distance == centre_distance);

	snake_el.set_direction(prev_dir);

	return centre_adj;
}

int snake_list::SnakeList::adj_snake(snake_unit::SnakeUnit & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_utils::direction_e dir1, snake_utils::direction_e dir2, snake_utils::direction_e curr_dir, int win_dim_mov) {
	std::vector<snake_unit::SnakeUnit> & snake_vector (this->get_vector());

	int centre_distance = ((curr_dim + prev_dim)/2);
	int adjustment = 0;
	// Coordinate that must be aligned when moving
	// X for vertical movement
	// Y for horizontal movement
	int diff = (int) abs(curr_coord_perp_dir - prev_coord_perp_dir);
	if (diff > 0) {
		if (diff < speed) {
			adjustment = diff;
		} else {
			adjustment = speed;
		}
		// Change direction to align with previous unit
		if (curr_coord_perp_dir > prev_coord_perp_dir) {
			snake_el.set_direction(dir1);
		} else {
			snake_el.set_direction(dir2);
		}
		ASSERT(adjustment >= 0);
	} else {
		int adj_prev_coord_mov_dir = prev_coord_mov_dir;
		// Deal with case where snake appears on the other side of the screen
		if ((curr_dir == snake_utils::direction_e::RIGHT) || (curr_dir == snake_utils::direction_e::UP)) {
			if (curr_coord_mov_dir > prev_coord_mov_dir) {
				adj_prev_coord_mov_dir = prev_coord_mov_dir + win_dim_mov;
			} else {
				adj_prev_coord_mov_dir = prev_coord_mov_dir;
			}
		} else if ((curr_dir == snake_utils::direction_e::LEFT) || (curr_dir == snake_utils::direction_e::DOWN)) {
			if (curr_coord_mov_dir < prev_coord_mov_dir) {
				adj_prev_coord_mov_dir = prev_coord_mov_dir - win_dim_mov;
			} else {
				adj_prev_coord_mov_dir = prev_coord_mov_dir;
			}
		}
		adjustment = centre_distance - ((int) abs(curr_coord_mov_dir - adj_prev_coord_mov_dir));
		// For head adjustment is equal to centre_distance because curr and prev coord are identicals
		if (snake_el != snake_vector.front()) {
			ASSERT(adjustment == 0);
		}

	}


	return adjustment;
}

#ifndef HARD_WALL
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif // HARD_WALL
void snake_list::SnakeList::check_collision(const int & win_width, const int & win_height) {
	check_snake_collision();
	#ifdef HARD_WALL
	bool hard_wall = snake_settings.get_hard_wall_flag();
	if (hard_wall == true) {
		check_wall_collision(win_width, win_height);
	}
	#endif // HARD_WALL
}
#ifndef HARD_WALL
#pragma GCC diagnostic pop
#endif // HARD_WALL

#ifdef HARD_WALL
void snake_list::SnakeList::check_wall_collision(const int & win_width, const int & win_height) {

	std::vector<snake_unit::SnakeUnit> & snake_vector (this->get_vector());

	for(auto snake_el : snake_vector) {

		int x_centre = snake_el.get_x_centre();
		int y_centre = snake_el.get_y_centre();
		int height = snake_el.get_height();
		int width = snake_el.get_width();

		int coord = 0;

		coord = y_centre + height/2;
		if (coord > win_height) {
			GAME_OVER("Snake unit is crossing the hard wall at the top of the window. Snake Unit coordinate (Valid value: 0 to ", win_height, "): ", coord);
		}

		coord = y_centre - height/2;
		if (coord < 0) {
			GAME_OVER("Snake unit is crossing the hard wall at the bottom of the window. Snake Unit coordinate (Valid value: 0 to ", win_height, "): ", coord);
		}

		coord = x_centre + width/2;
		if (coord > win_width) {
			GAME_OVER("Snake unit is crossing the hard wall on the right hand side of the window. Snake Unit coordinate (Valid value: 0 to ", win_width, "): ", coord);
		}

		coord = x_centre - width/2;
		if (coord < 0) {
			GAME_OVER("Snake unit is crossing the hard wall on the right hand side of the window. Snake Unit coordinate (Valid value: 0 to ", win_width, "): ", coord);
		}

	}

}
#endif // HARD_WALL

void snake_list::SnakeList::check_snake_collision() {

	std::vector<snake_unit::SnakeUnit> & snake_vector (this->get_vector());

	for(std::vector<snake_unit::SnakeUnit>::iterator unit1_it = snake_vector.begin(); unit1_it != snake_vector.end(); ++unit1_it) {

		int index_unit1 = std::distance(snake_vector.begin(), unit1_it);
		snake_unit::SnakeUnit unit1(snake_vector.at(index_unit1));

		snake_utils::direction_e direction1(unit1.get_direction());
		int x_centre1 = unit1.get_x_centre();
		int y_centre1 = unit1.get_y_centre();
		int height1 = unit1.get_height();
		int width1 = unit1.get_width();

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Check Collision] Current Unit: X ", x_centre1, " Y ", y_centre1, " Height ", height1, " Width ", width1);

		if (unit1_it != snake_vector.end()) {

			std::vector<snake_unit::SnakeUnit>::iterator unit1_next_it(std::next(unit1_it, 1));

			if (unit1_next_it != snake_vector.end()) {

				// Consecutive pointer distance check is already performed by move function.
				// When the direction changes, the centres of consecutive snake units may be closer than the expected distance
				for(std::vector<snake_unit::SnakeUnit>::iterator unit2_it = std::next(unit1_next_it,1); unit2_it != snake_vector.end(); ++unit2_it) {

					int index_unit2 = std::distance(snake_vector.begin(), unit2_it);
					snake_unit::SnakeUnit unit2(snake_vector.at(index_unit2));

					// Store values of current element before updating its position and direction
					int x_centre2 = unit2.get_x_centre();
					int y_centre2 = unit2.get_y_centre();
					int height2 = unit2.get_height();
					int width2 = unit2.get_width();

					LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Check Collision] Previous Unit: X ", x_centre2, " Y ", y_centre2, " Height ", height2, " Width ", width2);

					int y_centre_distance = (height1 + height2)/2;
					int x_centre_distance = (width1 + width2)/2;
					int total_centre_distance = x_centre_distance + y_centre_distance;

					int x_dist = (int) abs(x_centre1 - x_centre2);
					int y_dist = (int) abs(y_centre1 - y_centre2);
					int tot_dist = x_dist + y_dist;

					if ((x_dist < x_centre_distance) && (y_dist < y_centre_distance)) {
						// Unit1 and Unit2 are getting closer to each other on the x axis
						if (((x_centre1 >= x_centre2) && (direction1 == snake_utils::direction_e::RIGHT)) || ((x_centre1 <= x_centre2) && (direction1 == snake_utils::direction_e::LEFT))) {
							if (tot_dist < total_centre_distance) {
								GAME_OVER("Collision on the X axis. X coordinates: Unit1 -> ", x_centre1, " - Unit2 -> ", x_centre2, " Y coordinates: Unit1 -> ", y_centre1, " - Unit2 -> ", y_centre2, ". Calculated distance: X axis ", x_dist, ", Y axis ", y_dist);
							}
						}

						// Unit1 and Unit2 are getting closer to each other on the y axis
						if (((y_centre1 >= y_centre2) && (direction1 == snake_utils::direction_e::DOWN)) || ((y_centre1 <= y_centre2) && (direction1 == snake_utils::direction_e::UP))) {
							if (tot_dist < total_centre_distance) {
								GAME_OVER("Collision on the Y axis. X coordinates: Unit1 -> ", x_centre1, " - Unit2 -> ", x_centre2, " Y coordinates: Unit1 -> ", y_centre1, " - Unit2 -> ", y_centre2, ". Calculated distance: X axis ", x_dist, ", Y axis ", y_dist);
							}
						}
					}

				}
			}


		}

	}
}

int snake_list::SnakeList::compute_centre_distance(int coord1, int coord2, int win_dim, int exp_distance) {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Compute Centre Distance] Coordinate1: ", coord1, " Coordinate2: ", coord2, " Window dimension ", win_dim, " Expected distance ", exp_distance);
	int distance = (int) abs(coord1 - coord2);
	ASSERT(distance <= win_dim);
	// Units are on oposite sides of the screen
	if (distance > exp_distance) {
		distance = win_dim - distance;
	}

	ASSERT(distance <= exp_distance);

	LOG_INFO(logging::verb_level_e::DEBUG, "[Compute Centre Distance] Calculated distance: ", distance);
	return distance;
}

