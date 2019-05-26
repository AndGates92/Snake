/**
 * @copyright
 * @file snake_list.cpp
 * @author Andrea Gianarda
 * @date 05th March 2019
 * @brief Snake List function
 */

#include <iostream>
#include <cmath>

#include "colours.h"
#include "settings.h"
#include "game_graphics.h"
#include "basic_obj_list.h"
#include "snake_list.h"
#include "snake_node.h"
#include "logging.h"

using namespace std;
using namespace logging;
using namespace snake_list;
using namespace snake_node;
using namespace colours;
using namespace game_graphics;

snake_list::SnakeList::~SnakeList() {

	std::string pretext ("Destructor");
	this->print_info(logging::verb_level_e::LOW, pretext);

	this->~BasicObjList();

	LOG_INFO(logging::verb_level_e::HIGH, "Snake list destroyed");

}

// Add nodes from the head down
void snake_list::SnakeList::add_node(int centre_x, int centre_y, int snake_width, int snake_height, snake_utils::direction_e snake_direction, colours::palette_e snake_colour) {

	snake_node::SnakeNode * head = this->get_head();
	std::string name = this->get_name();

	LOG_INFO(logging::verb_level_e::LOW, "[Add Node] Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	snake_node::SnakeNode * new_snake = new snake_node::SnakeNode(name, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour);
	if (new_snake == nullptr) {
		LOG_ERROR("Can't allocate memory for snake node Name: ", name, " Centre coordinares: (X ", centre_x, ", Y ", centre_y, "), width ", snake_width, ", height ", snake_height, ",  direction ", snake_direction, " colour ", snake_colour, ".");
	}

cout << "Scan snake list -> centre: (" << centre_x << ", " << centre_y << ")" <<  endl;
cout << "Snake direction: " << snake_direction << endl;

	if(head != nullptr) {
		snake_node::SnakeNode * snake_list = head;
		snake_node::SnakeNode * snake_found = nullptr;

		int width_head = head->get_width();
		ASSERT(width_head == snake_width)

		int height_head = head->get_height();
		ASSERT(height_head == snake_height)

		while (snake_list != nullptr) {
//			int prev_x = 0;
//			int prev_y = 0;

			int curr_x = snake_list->get_x_centre();
			int curr_y = snake_list->get_y_centre();

//			if (snake_list->get_prev() != nullptr) {
//				prev_x = snake_list->get_prev()->get_x_centre();
//				prev_y = snake_list->get_prev()->get_y_centre();

cout << "X: curr " << curr_x << " centre_x " << centre_x << endl; // << " prev " << prev_x << endl;
cout << "Y: curr " << curr_y << " centre_y " << centre_y << endl; //" prev " << prev_y << endl;
//				if ((((int) abs(curr_x - centre_x)) <= snake_width) && (((int) abs(prev_x - centre_x)) <= snake_width) || (((int) abs(curr_y - centre_y)) <= snake_height) && (((int) abs(prev_y - centre_y)) <= snake_height)) {
				if (
					    ((((int) abs(curr_x - centre_x)) <= snake_width) & ((snake_direction == snake_utils::direction_e::RIGHT) | (snake_direction == snake_utils::direction_e::LEFT)))
					 || ((((int) abs(curr_y - centre_y)) <= snake_height) & ((snake_direction == snake_utils::direction_e::UP) | (snake_direction == snake_utils::direction_e::DOWN)))
				) {
					snake_found = snake_list;
//cout << "Snake found" << endl;
				}
//			}
//cout << "Snake found " << snake_found << " snake list " << snake_list << endl;
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

			snake_utils::direction_e direction_found = snake_found->get_direction();
			ASSERT(direction_found == snake_direction)

			int x_centre_found = snake_found->get_x_centre();
			int y_centre_found = snake_found->get_y_centre();

			int hdistance_units = 0;
			int hdistance_measured = 0;
			int vdistance_units = 0;
			int vdistance_measured = 0;
			if ((direction_found == snake_utils::direction_e::RIGHT) | (direction_found == snake_utils::direction_e::LEFT)) {
				hdistance_units = (snake_width/2) + (width_found/2);
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = 0;
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			} else if ((direction_found == snake_utils::direction_e::UP) | (direction_found == snake_utils::direction_e::DOWN)) {
				hdistance_units = 0;
				hdistance_measured = ((int) abs(centre_x - x_centre_found));
				vdistance_units = (snake_height/2) + (height_found/2);
				vdistance_measured = ((int) abs(centre_y - y_centre_found));
			}

//cout << "Direction " << direction_found << endl;
//cout << "centre_y " << centre_x << " y_centre_found " << x_centre_found << " H dist units " << hdistance_units << " measured " << hdistance_measured << endl;
			ASSERT(hdistance_units == hdistance_measured)
//cout << "centre_x " << centre_y << " x_centre_found " << y_centre_found << " V dist units " << vdistance_units << " measured " << vdistance_measured << endl;
			ASSERT(vdistance_units == vdistance_measured)

			// If direction is down or left, add after the element found
			if ((snake_direction == snake_utils::direction_e::DOWN) | (snake_direction == snake_utils::direction_e::LEFT)) {
				new_snake->set_next(snake_found->get_next());
				new_snake->set_prev(snake_found);
				snake_found->set_next(new_snake);
			} else {
				new_snake->set_prev(snake_found->get_prev());
				new_snake->set_next(snake_found);
				snake_found->set_prev(new_snake);
				if (snake_found == head) {
					this->set_head(new_snake);
				}
			}
//			snake_found->get_prev()->set_next(new_snake);
		}
	} else {
		new_snake->set_prev(nullptr);
		new_snake->set_next(nullptr);
		this->set_head(new_snake);
	}

}

void snake_list::SnakeList::move(const int & speed, const int & win_width, const int & win_height, const snake_utils::direction_e & head_dir) {
	LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Window dimensions: Width ", win_width, " Height ", win_height, " Speed: ", speed);

	snake_node::SnakeNode * head (this->get_head());

	snake_node::SnakeNode * snake_el (head);

	snake_utils::direction_e direction_prev = head_dir;
	int x_centre_prev = head->get_x_centre();
	int y_centre_prev = head->get_y_centre();
	int height_prev = head->get_height();
	int width_prev = head->get_width();

	snake_utils::direction_e direction_curr = head->get_direction();
	int x_centre_curr = head->get_x_centre();
	int y_centre_curr = head->get_y_centre();
	int height_curr = head->get_height();
	int width_curr = head->get_width();


	snake_settings.set_head_centre_x(x_centre_curr);
	snake_settings.set_head_centre_y(y_centre_curr);
	snake_settings.set_head_dir(direction_curr);

//cout << "Move snake - Window dimensions: width " << win_width << " height " << win_height << endl;
	int speed_int = speed;

	while (snake_el != nullptr) {

		// Store values of current element before updating its position and direction
		direction_curr = snake_el->get_direction();
		x_centre_curr = snake_el->get_x_centre();
		y_centre_curr = snake_el->get_y_centre();
		height_curr = snake_el->get_height();
		width_curr = snake_el->get_width();

//cout << "Direction prev " << direction_prev << " curr " << direction_curr << endl;
cout << " x_centre_curr " << x_centre_curr << " x_centre_prev " << x_centre_prev <<" y_centre_curr " << y_centre_curr << " y_centre_prev " << y_centre_prev << endl;

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Current Unit: X ", x_centre_curr, " Y ", y_centre_curr, " Direction ", direction_curr);
		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Move] Previous Unit: X ", x_centre_prev, " Y ", y_centre_prev, " Direction ", direction_prev);

		if (direction_prev != direction_curr) {
			if (snake_el != head) {
				int sign = 0;
				// UP
				if ((direction_prev == snake_utils::direction_e::UP) | (direction_prev == snake_utils::direction_e::RIGHT)) {
					sign = -1;
				} else {
					sign = 1;
				}

				ASSERT((sign == 1) | (sign == -1));

				int height_centre_distance = (height_curr + height_prev)/2;
				int y_diff = abs(y_centre_curr - y_centre_prev);
				int width_centre_distance = (width_curr + width_prev)/2;
				int x_diff = abs(x_centre_curr - x_centre_prev);
//cout << "Diff X " << x_diff << " Y " << y_diff << endl;
//cout << "Centre distance Width " << width_centre_distance << " height " << height_centre_distance << endl;
//cout << "Direction current " << direction_curr << " previous " << direction_prev << endl;
				if (((direction_curr == snake_utils::direction_e::RIGHT) & (direction_prev == snake_utils::direction_e::LEFT)) | ((direction_curr == snake_utils::direction_e::LEFT) & (direction_prev == snake_utils::direction_e::RIGHT))) {
					if ((y_diff < height_centre_distance) & (x_diff < width_centre_distance)) {
						LOG_ERROR("Units moving in opposite horizintal movement and colliding");
					}
				} else if (((direction_curr == snake_utils::direction_e::UP) & (direction_prev == snake_utils::direction_e::DOWN)) | ((direction_curr == snake_utils::direction_e::DOWN) & (direction_prev == snake_utils::direction_e::UP))) {
					if ((x_diff < width_centre_distance) & (y_diff < height_centre_distance)) {
						LOG_ERROR("Units moving in opposite vertical movement and colliding");
					}
				}

				// Consecutive units can't travel in opposite direction
				ASSERT(
					((direction_curr == snake_utils::direction_e::RIGHT) & (direction_prev != snake_utils::direction_e::LEFT))  |
					((direction_curr == snake_utils::direction_e::LEFT)  & (direction_prev != snake_utils::direction_e::RIGHT)) |
					((direction_curr == snake_utils::direction_e::UP)    & (direction_prev != snake_utils::direction_e::DOWN))  |
					((direction_curr == snake_utils::direction_e::DOWN)  & (direction_prev != snake_utils::direction_e::UP))
				);

				// Adjust coordinate centres of pervious and current unit must be aligned as to ditance between centres is kept constant
				// Y for horizontal to vertical movement
				// X for vertical to horizontal movement
				if (((direction_curr == snake_utils::direction_e::RIGHT) | (direction_curr == snake_utils::direction_e::LEFT)) & ((int) abs(x_centre_prev - x_centre_curr) < speed)) {

					// Unit moving horizontally:
					// - X is force to aligned (set previous unit X coordinate)
					// - Y is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, win_height, height_curr, height_prev, y_centre_curr, y_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", x_centre_prev, " Y ", centre_adj);
					snake_el->set_x_centre(x_centre_prev);
					snake_el->set_y_centre(centre_adj);
				} else if (((direction_curr == snake_utils::direction_e::UP) | (direction_curr == snake_utils::direction_e::DOWN)) & ((int) abs(y_centre_prev - y_centre_curr) < speed)) {
					// Unit moving vertically:
					// - Y is force to aligned (set previous unit Y coordinate)
					// - X is adjusted to keep distance between centre constant
					int centre_adj = snake_list::SnakeList::change_dir(snake_el, win_width, width_curr, width_prev, x_centre_curr, x_centre_prev, sign, direction_prev);
					LOG_INFO(logging::verb_level_e::HIGH, "[Snake List Move] Change drection to ", direction_prev, " New coordinates X ", centre_adj, " Y ", y_centre_prev);
					snake_el->set_x_centre(centre_adj);
					snake_el->set_y_centre(y_centre_prev);
				}
			} else {
				snake_utils::direction_e direction_next = snake_el->get_next()->get_direction();
				// If head and second unit have the same direction, the head can change again
				if (direction_next == direction_curr) {
					snake_el->set_direction(direction_prev);
				}
			}
		} else {

			int adjustment = 0;

			if ((direction_curr == snake_utils::direction_e::RIGHT) | (direction_curr == snake_utils::direction_e::LEFT)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, width_curr, width_prev, x_centre_curr, x_centre_prev, y_centre_curr, y_centre_prev, speed, snake_utils::direction_e::DOWN, snake_utils::direction_e::UP, direction_curr, win_width);
			} else if ((direction_curr == snake_utils::direction_e::UP) | (direction_curr == snake_utils::direction_e::DOWN)) {
				adjustment = snake_list::SnakeList::adj_snake(snake_el, height_curr, height_prev, y_centre_curr, y_centre_prev, x_centre_curr, x_centre_prev, speed, snake_utils::direction_e::LEFT, snake_utils::direction_e::RIGHT, direction_curr, win_height);
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

int snake_list::SnakeList::change_dir(snake_node::SnakeNode * & snake_el, int win_dim, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int sign, snake_utils::direction_e prev_dir) {
	// Distance between centres
	int centre_distance = ((curr_dim + prev_dim)/2);
	int curr_distance = compute_centre_distance(curr_coord_mov_dir, prev_coord_mov_dir, win_dim, centre_distance);

	// Adjustment: distance between centres - actual distance between centres 
	int adjustment = centre_distance - curr_distance;
//cout << "adj " << adjustment << " centre dist " << centre_distance << " curr_coord_mov_dir " << curr_coord_mov_dir << " prev_coord_mov_dir " << prev_coord_mov_dir <<  endl;
	ASSERT((adjustment >= 0) & (adjustment <= centre_distance));

	int centre_adj = curr_coord_mov_dir + sign * adjustment;
	int adj_distance = compute_centre_distance(prev_coord_mov_dir, centre_adj, win_dim, centre_distance);

	if(adj_distance != centre_distance) {
		LOG_ERROR("Snake units are touching each other.\nUnit1 -> ", centre_adj, ". Unit2 -> ", prev_coord_mov_dir);
	}

	ASSERT(adj_distance == centre_distance);

	snake_el->set_direction(prev_dir);

	return centre_adj;
}

int snake_list::SnakeList::adj_snake(snake_node::SnakeNode * & snake_el, int curr_dim, int prev_dim, int curr_coord_mov_dir, int prev_coord_mov_dir, int curr_coord_perp_dir, int prev_coord_perp_dir, int speed, snake_utils::direction_e dir1, snake_utils::direction_e dir2, snake_utils::direction_e curr_dir, int win_dim_mov) {
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
		int adj_prev_coord_mov_dir = prev_coord_mov_dir;
		// Deal with case where snake appears on the other side of the screen
		if ((curr_dir == snake_utils::direction_e::RIGHT) | (curr_dir == snake_utils::direction_e::UP)) {
			if (curr_coord_mov_dir > prev_coord_mov_dir) {
				adj_prev_coord_mov_dir = prev_coord_mov_dir + win_dim_mov;
			} else {
				adj_prev_coord_mov_dir = prev_coord_mov_dir;
			}
		} else if ((curr_dir == snake_utils::direction_e::LEFT) | (curr_dir == snake_utils::direction_e::DOWN)) {
			if (curr_coord_mov_dir < prev_coord_mov_dir) {
				adj_prev_coord_mov_dir = prev_coord_mov_dir - win_dim_mov;
			} else {
				adj_prev_coord_mov_dir = prev_coord_mov_dir;
			}
		}
		adjustment = centre_distance - ((int) abs(curr_coord_mov_dir - adj_prev_coord_mov_dir));
//cout << "snake_el " << snake_el << " head ptr " << head << " adj " << adjustment << " centre dist " << centre_distance << " curr_coord_mov_dir " << curr_coord_mov_dir << " prev_coord_mov_dir " << prev_coord_mov_dir << " adj_prev_coord_mov_dir " << adj_prev_coord_mov_dir << " win_dim_move " << win_dim_mov <<  endl;
		// For head adjustment is equal to centre_distance because curr and prev coord are identicals
		if (snake_el != head) {
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

	snake_node::SnakeNode * head (this->get_head());

	snake_node::SnakeNode * snake (head);

	while (snake != nullptr) {

		int x_centre = snake->get_x_centre();
		int y_centre = snake->get_y_centre();
		int height = snake->get_height();
		int width = snake->get_width();

		for (int h = -height/2; h < height/2; h++) {
			int coord = y_centre + h;
			if ((coord < 0) | (coord > win_height)) {
				GAME_OVER("Snake unit is crossing the hard wall. Snake Unit coordinate (Valid value: 0 to ", win_height, "): ", coord);
			}
		}

		for (int w = -width/2; w < width/2; w++) {
			int coord = x_centre + w;
			if ((coord < 0) | (coord > win_width)) {
				GAME_OVER("Snake unit is crossing the hard wall. Snake Unit coordinate (Valid value: 0 to ", win_width, "): ", coord);
			}
		}

		snake = snake->get_next();

	}

}
#endif // HARD_WALL

void snake_list::SnakeList::check_snake_collision() {

	snake_node::SnakeNode * head (this->get_head());

	snake_node::SnakeNode * snake1 (head);

	while (snake1 != nullptr) {

		snake_utils::direction_e direction1 = snake1->get_direction();
		int x_centre1 = snake1->get_x_centre();
		int y_centre1 = snake1->get_y_centre();
		int height1 = snake1->get_height();
		int width1 = snake1->get_width();

//cout << " x_centre1 " << x_centre1 <<" y_centre1 " << y_centre1 << endl;

		LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Check Collision] Current Unit: X ", x_centre1, " Y ", y_centre1, " Height ", height1, " Width ", width1);
		snake_node::SnakeNode * snake1_nxt (snake1->get_next());

		// Consecutive pointer distance check is already performed by move function.
		// When the direction changes, the centres of consecutive snake units may be closer than the expected distance
		if (snake1_nxt != nullptr) {

//cout << " x_centre1 nxt " << snake1_nxt->get_x_centre() <<" y_centre1 nxt " << snake1_nxt->get_y_centre() << endl;
			snake_node::SnakeNode * snake2 (snake1_nxt->get_next());

			while (snake2 != nullptr) {
				// Store values of current element before updating its position and direction
				int x_centre2 = snake2->get_x_centre();
				int y_centre2 = snake2->get_y_centre();
				int height2 = snake2->get_height();
				int width2 = snake2->get_width();

//cout << " x_centre2 " << x_centre2 <<" y_centre2 " << y_centre2 << endl;

				LOG_INFO(logging::verb_level_e::DEBUG, "[Snake List Check Collision] Previous Unit: X ", x_centre2, " Y ", y_centre2, " Height ", height2, " Width ", width2);

				int y_centre_distance = (height1 + height2)/2;
				int x_centre_distance = (width1 + width2)/2;
				int total_centre_distance = x_centre_distance + y_centre_distance;

//cout << " exp_x_distance " << x_centre_distance <<" exp_y_distance " << y_centre_distance << endl;

				int x_dist = (int) abs(x_centre1 - x_centre2);
				int y_dist = (int) abs(y_centre1 - y_centre2);
				int tot_dist = x_dist + y_dist;

				// Unit1 and Unit2 are getting closer to each other on the x axis
				if (((x_centre1 >= x_centre2) & (direction1 == snake_utils::direction_e::RIGHT)) | ((x_centre1 <= x_centre2) & (direction1 == snake_utils::direction_e::LEFT))) {
					if (tot_dist < total_centre_distance) {
						GAME_OVER("Collision on the X axis. X coordinates: Unit1 -> ", x_centre1, " - Unit2 -> ", x_centre2, " Y coordinates: Unit1 -> ", y_centre1, " - Unit2 -> ", y_centre2, ". Calculated distance: X axis ", x_dist, ", Y axis ", y_dist);
					}
				}

				// Unit1 and Unit2 are getting closer to each other on the y axis
				if (((y_centre1 >= y_centre2) & (direction1 == snake_utils::direction_e::DOWN)) | ((y_centre1 <= y_centre2) & (direction1 == snake_utils::direction_e::UP))) {
					if (tot_dist < total_centre_distance) {
						GAME_OVER("Collision on the Y axis. X coordinates: Unit1 -> ", x_centre1, " - Unit2 -> ", x_centre2, " Y coordinates: Unit1 -> ", y_centre1, " - Unit2 -> ", y_centre2, ". Calculated distance: X axis ", x_dist, ", Y axis ", y_dist);
					}
				}

				snake2 = snake2->get_next();
			}

		}

		snake1 = snake1_nxt;

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

//cout << " coord1 " << coord1 <<" coord2 " << coord2 << " distance " << distance << " exp distance " << exp_distance << endl;

	ASSERT(distance <= exp_distance);

	LOG_INFO(logging::verb_level_e::DEBUG, "[Compute Centre Distance] Calculated distance: ", distance);
	return distance;
}
