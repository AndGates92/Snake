/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>
#include <cmath>

#include "game_graphics.h"
#include "basic_obj_list.h"
#include "graphics_utils.h"
#include "snake_list.h"
#include "snake_node.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace snake_list;
using namespace snake_node;
using namespace graphics_utils;
using namespace game_graphics;

snake_list::SnakeList::~SnakeList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	this->~BasicObjList();

	LOG_INFO(logging::verb_level_e::HIGH, "Snake list destroyed");

}


void snake_list::SnakeList::add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_node::direction_e snake_direction, graphics_utils::palette_e snake_colour) {

	snake_node::SnakeNode * head = this->get_head();
	std::string name = this->get_name();

	LOG_INFO(logging::verb_level_e::LOW, "[Add Node] Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	snake_node::SnakeNode * new_snake = new snake_node::SnakeNode(name, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour);
	if (new_snake == nullptr) {
		LOG_ERROR("Can't allocate memory for snake node Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	}

	if(head != nullptr) {
		snake_node::SnakeNode * snake_list = head;
		snake_node::SnakeNode * snake_found = nullptr;

		int width_head = head->get_width();
		ASSERT(width_head == snake_width)

		int height_head = head->get_height();
		ASSERT(height_head == snake_height)



		while (snake_list != nullptr) {
			int prev_x = 0;
			int prev_y = 0;

			int curr_x = snake_list->get_x_centre();
			int curr_y = snake_list->get_y_centre();

			if (snake_list->get_prev() != nullptr) {
				prev_x = snake_list->get_prev()->get_x_centre();
				prev_y = snake_list->get_prev()->get_y_centre();

				if ((((int) abs(curr_x - centre_x)) <= snake_width) && (((int) abs(prev_x - centre_x)) <= snake_width) && (((int) abs(curr_y - centre_y)) <= snake_height) && (((int) abs(prev_y - centre_y)) <= snake_height)) {
					snake_found = snake_list;
				}
			}
			snake_list = snake_list->get_next();
		}

		if (snake_found == nullptr) {
			snake_node::SnakeNode * snake_head = head;

			new_snake->set_next(snake_head);
			new_snake->set_prev(nullptr);
			snake_head->set_prev(new_snake);

			if (snake_head == head) {
				this->set_head(new_snake);
			}
		} else {
			int width_found = snake_found->get_width();
			ASSERT(width_found == snake_width)

			int height_found = snake_found->get_height();
			ASSERT(height_found == snake_height)

			snake_node::direction_e direction_found = snake_found->get_direction();
			ASSERT(direction_found == snake_direction)

			int x_centre_found = snake_found->get_x_centre();
			int y_centre_found = snake_found->get_y_centre();

			int hdistance_units = 0;
			int hdistance_measured = 0;
			int vdistance_units = 0;
			int vdistance_measured = 0;
			if ((direction_found == snake_node::direction_e::RIGHT) | (direction_found == snake_node::direction_e::LEFT)) {
				hdistance_units = (snake_width/2) + (width_found/2);
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = 0;
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			} else if ((direction_found == snake_node::direction_e::UP) | (direction_found == snake_node::direction_e::DOWN)) {
				hdistance_units = 0;
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = (snake_height/2) + (height_found/2);
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			}

			ASSERT(hdistance_units == hdistance_measured)
			ASSERT(vdistance_units == vdistance_measured)

			new_snake->set_prev(snake_found->get_prev());
			new_snake->set_next(snake_found);
			snake_found->set_prev(new_snake);
			snake_found->get_prev()->set_next(new_snake);
		}
	} else {
		new_snake->set_prev(nullptr);
		new_snake->set_next(nullptr);
		this->set_head(new_snake);
	}

}

void snake_list::SnakeList::move(int speed, int win_width, int win_height, snake_node::direction_e head_dir) {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Window dimensions: Width ", win_width, " Height ", win_height, " Speed: ", speed);

	snake_node::SnakeNode * head (this->get_head());

	snake_node::SnakeNode * snake_el (head);

	snake_node::direction_e direction_prev = head_dir;
	int x_centre_prev = head->get_x_centre();
	int y_centre_prev = head->get_y_centre();
	int height_prev = head->get_height();
	int width_prev = head->get_width();

	snake_node::direction_e direction_curr = head->get_direction();
	int x_centre_curr = head->get_x_centre();
	int y_centre_curr = head->get_y_centre();
	int height_curr = head->get_height();
	int width_curr = head->get_width();

cout << "Move snake" << endl;
	int speed_int = speed;

	while (snake_el != nullptr) {

		// Store values of current element before updating its position and direction
		direction_curr = snake_el->get_direction();
		x_centre_curr = snake_el->get_x_centre();
		y_centre_curr = snake_el->get_y_centre();
		height_curr = snake_el->get_height();
		width_curr = snake_el->get_width();

cout << "Direction prev " << direction_prev << " curr " << direction_curr << endl;
cout << " x_centre_curr " << x_centre_curr << " x_centre_prev " << x_centre_prev <<" y_centre_curr " << y_centre_curr << " y_centre_prev " << y_centre_prev << endl;

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Current Unit: X ", x_centre_curr, " Y ", y_centre_curr, " Direction ", direction_curr);
		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Previous Unit: X ", x_centre_prev, " Y ", y_centre_prev, " Direction ", direction_prev);

		if (direction_prev != direction_curr) {
			if (snake_el != head) {
				int sign = 0;
				// UP
				if ((direction_prev == snake_node::direction_e::UP) | (direction_prev == snake_node::direction_e::RIGHT)) {
					sign = -1;
				} else {
					sign = 1;
				}

				ASSERT((sign == 1) | (sign == -1));

				int height_centre_distance = (height_curr + height_prev)/2;
				int y_diff = abs(y_centre_curr - y_centre_prev);
				int width_centre_distance = (width_curr + width_prev)/2;
				int x_diff = abs(x_centre_curr - x_centre_prev);
				if (((direction_curr == snake_node::direction_e::RIGHT) & (direction_prev == snake_node::direction_e::LEFT)) | ((direction_curr == snake_node::direction_e::LEFT) & (direction_prev == snake_node::direction_e::RIGHT))) {
					if ((y_diff < height_centre_distance) & (x_diff == width_centre_distance)) {
						LOG_ERROR("Units moving in opposite horizintal movement and colliding");
					}
				} else if (((direction_curr == snake_node::direction_e::UP) & (direction_prev == snake_node::direction_e::DOWN)) | ((direction_curr == snake_node::direction_e::DOWN) & (direction_prev != snake_node::direction_e::UP))) {
					if ((x_diff < width_centre_distance) & (y_diff == height_centre_distance)) {
						LOG_ERROR("Units moving in opposite vertical movement and colliding");
					}
				}

				// Consecutive units can't travel in opposite direction
				ASSERT(
					((direction_curr == snake_node::direction_e::RIGHT) & (direction_prev != snake_node::direction_e::LEFT))  |
					((direction_curr == snake_node::direction_e::LEFT)  & (direction_prev != snake_node::direction_e::RIGHT)) |
					((direction_curr == snake_node::direction_e::UP)    & (direction_prev != snake_node::direction_e::DOWN))  |
					((direction_curr == snake_node::direction_e::DOWN)  & (direction_prev != snake_node::direction_e::UP))
				);

				// Adjust coordinate centres of pervious and current unit must be aligned as to ditance between centres is kept constant
				// Y for horizontal to vertical movement
				// X for vertical to horizontal movement
				if (((direction_curr == snake_node::direction_e::RIGHT) | (direction_curr == snake_node::direction_e::LEFT)) & ((int) abs(x_centre_prev - x_centre_curr) < speed)) {

					// Unit moving horizontally:
					// - X is force to aligned (set previous unit X coordinate)
					// - Y is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, height_curr, height_prev, y_centre_curr, y_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", x_centre_prev, " Y ", centre_adj);
					snake_el->set_x_centre(x_centre_prev);
					snake_el->set_y_centre(centre_adj);
				} else if (((direction_curr == snake_node::direction_e::UP) | (direction_curr == snake_node::direction_e::DOWN)) & ((int) abs(y_centre_prev - y_centre_curr) < speed)) {
					// Unit moving vertically:
					// - Y is force to aligned (set previous unit Y coordinate)
					// - X is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, width_curr, width_prev, x_centre_curr, x_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", centre_adj, " Y ", y_centre_prev);
					snake_el->set_x_centre(centre_adj);
					snake_el->set_y_centre(y_centre_prev);
				}
			} else {
				snake_el->set_direction(direction_prev);
			}
		} else {

			int adjustment = 0;

			if ((direction_curr == snake_node::direction_e::RIGHT) | (direction_curr == snake_node::direction_e::LEFT)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, width_curr, width_prev, x_centre_curr, x_centre_prev, y_centre_curr, y_centre_prev, speed, snake_node::direction_e::DOWN, snake_node::direction_e::UP, win_height);
			} else if ((direction_curr == snake_node::direction_e::UP) | (direction_curr == snake_node::direction_e::DOWN)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, height_curr, height_prev, y_centre_curr, y_centre_prev, x_centre_curr, x_centre_prev, speed, snake_node::direction_e::LEFT, snake_node::direction_e::RIGHT, win_width);
			}

			if ((adjustment == 0) | (snake_el == head)) {
				speed_int = speed;
			} else {
				if (adjustment <= speed) {
					speed_int = adjustment;
				} else {
					speed_int = 0;
				}
			}

		}


cout << "speed " << speed_int << endl;

		snake_el->move(speed_int, win_width, win_height);

		snake_el = snake_el->get_next();

		// Store values of previous element before updating its position and direction
		direction_prev = direction_curr;
		x_centre_prev = x_centre_curr;
		y_centre_prev = y_centre_curr;
		height_prev = height_curr;
		width_prev = width_curr;

	}
}

int snake_list::SnakeList::change_dir(snake_node::SnakeNode * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_node::direction_e prev_dir) {
	// Distance between centres
	int centre_distance = ((curr_dim + prev_dim)/2);
	// Adjustment: distance between centres - actual distance between centres 
	int adjustment = centre_distance - ((int) abs(curr_coord_mov_dir - prev_coord_mov_dir));
cout << "adj " << adjustment << " centre dist " << centre_distance << " curr_coord_mov_dir " << curr_coord_mov_dir << " prev_coord_mov_dir " << prev_coord_mov_dir <<  endl;
	int centre_adj = curr_coord_mov_dir + sign * adjustment;

	snake_el->set_direction(prev_dir);
	if((int) abs(prev_coord_mov_dir - centre_adj) != centre_distance) {
		LOG_ERROR("Snake units are touching each other.\nUnit1 -> ", centre_adj, ". Unit2 -> ", prev_coord_mov_dir);
	}

	ASSERT((int) abs(prev_coord_mov_dir - centre_adj) == centre_distance);

	ASSERT(adjustment >= 0);

	return centre_adj;
}

int snake_list::SnakeList::adj_snake(snake_node::SnakeNode * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_node::direction_e dir1, snake_node::direction_e dir2, int win_dim_mov) {
	snake_node::SnakeNode * head (this->get_head());
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
			snake_el->set_direction(dir1);
		} else {
			snake_el->set_direction(dir2);
		}
		ASSERT(adjustment >= 0);
	} else {
		adjustment = centre_distance - ((int) abs(curr_coord_mov_dir - prev_coord_mov_dir));
cout << "adj " << adjustment << " centre dist " << centre_distance << " curr_coord_mov_dir " << curr_coord_mov_dir << " prev_coord_mov_dir " << prev_coord_mov_dir << " win_dim_move " << win_dim_mov <<  endl;
		// For head adjustment is equal to centre_distance because curr and prev coord are identicals
		if (snake_el != head) {
			ASSERT(adjustment == 0);
		}

	}


	return adjustment;
}
