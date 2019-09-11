#ifndef INSERT_SNAKE_UNIT_H
#define INSERT_SNAKE_UNIT_H
/**
 * @copyright
 * @file insert_snake_unit.h
 * @author Andrea Gianarda
 * @date 22nd of August 2019
 * @brief insert_snake_unit header file
*/

#include "logging.h"

/** @defgroup InsertSnakeUnitGroup Doxygen Group
 *  Insert snake unit functions and classes
 *  @{
 */
namespace insert_snake_unit {
	/**
	 * @brief InsertSnakeUnit class
	 *
	 */
	template <typename direction_type, class class_type>
	class InsertSnakeUnit {
		public:
			// Constructor
			/**
			 * @brief Function: InsertSnakeUnit(element_type element)
			 *
			 * \param name_win: name of the WindowList
			 *
			 * InsertSnakeUnit constructor
			 */
			explicit InsertSnakeUnit(int x, int y, direction_type direction): snake_direction(direction), centre_x(x), centre_y(y) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Constructor of object InsertSnakeUnit. Searched element: ", direction)
			};

			/**
			 * @brief Function: bool is_neightbour(int & curr_x, int & curr_y, direction_type dir)
			 *
			 * \param curr_x: current x coordinate
			 * \param curr_y: current y coordinate
			 * \param dir: direction
			 *
			 * \return new unit coodinates are close enough to current snake unit
			 *
			 * Look for neightbour
			 */
			bool is_neightbour(int & curr_x, int & curr_y, direction_type dir) const;

			/**
			 * @brief Function: bool operator()(class_type unit) const
			 *
			 * \param unit: snake unit to process
			 *
			 * \return whether a new unit needs to be added at the current location
			 *
			 * Determine whether the new unit should be inserted next to the current unit
			 */
			bool operator()(class_type unit) const;

		protected:

		private:
			direction_type snake_direction;
			int centre_x;
			int centre_y;
	};
}
/** @} */ // End of InsertSnakeUnitGroup group

template <typename direction_type, class class_type>
bool insert_snake_unit::InsertSnakeUnit<direction_type, class_type>::operator()(class_type unit) const {
	int curr_x = unit.get_x_centre();
	int curr_y = unit.get_y_centre();
	direction_type curr_snake_dir = unit.get_direction();

	bool found = false;

	bool found_neightbour_same_dir = this->is_neightbour(curr_x, curr_y, this->snake_direction);
	bool found_neightbour_diff_dir = this->is_neightbour(curr_x, curr_y, curr_snake_dir);

	if (curr_snake_dir == this->snake_direction) {
		if (found_neightbour_same_dir == true) {
			found = true;
		}
	} else {
		if ((found_neightbour_same_dir == true) || (found_neightbour_diff_dir == true)) {
			found = true;
		}
	}

	return found;
}

template <typename direction_type, class class_type>
bool insert_snake_unit::InsertSnakeUnit<direction_type, class_type>::is_neightbour(int & curr_x, int & curr_y, direction_type dir) const {

	bool found_neightbour = false;

	if (
		// LEFT: X coordinate of the head is smaller that coordinate of other snake units
		   ((curr_x >= this->centre_x) && (curr_y == this->centre_y) && (dir == direction_type::LEFT))
		// RIGHT: X coordinate of the head is larger that coordinate of other snake units
		|| ((curr_x < this->centre_x)  && (curr_y == this->centre_y) && (dir == direction_type::RIGHT))
		// DOWN: Y coordinate of the head is smaller that coordinate of other snake units
		|| ((curr_y >= this->centre_y) && (curr_x == this->centre_x) && (dir == direction_type::DOWN))
		// UP: Y coordinate of the head is larger that coordinate of other snake units
		|| ((curr_y < this->centre_y)  && (curr_x == this->centre_x) && (dir == direction_type::UP))
	) {
		found_neightbour = true;
	} else {
		found_neightbour = false;
	}

	return found_neightbour;
}

#endif // INSERT_SNAKE_UNIT_H
