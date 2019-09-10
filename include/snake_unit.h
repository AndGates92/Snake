#ifndef SNAKE_UNIT_H
#define SNAKE_UNIT_H
/**
 * @copyright
 * @file snake_unit.h
 * @author Andrea Gianarda
 * @date 03rd of March 2019
 * @brief Snake unit header file
*/

#include "basic_object.h"
#include "snake_utils.h"
#include "colours.h"

/** @defgroup SnakeUnitGroup Snake Unit Doxygen Group
 *  Snake Unit functions and classes
 *  @{
 */
namespace snake_unit {

	namespace {
		/**
		 * @brief Initial speed
		 *
		 */
		const static snake_utils::direction_e init_direction = snake_utils::direction_e::RIGHT;

		/**
		 * @brief Unit Height
		 *
		 */
		const static int init_node_height = 10;

		/**
		 * @brief Unit Width
		 *
		 */
		const static int init_node_width = 10;
	}

	/**
	 * @brief SnakeUnit class
	 *
	 */
	class SnakeUnit : public basic_object::BasicObject {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeUnit(std::string name_unit = "Snake Unit", int centre_x = 0, int centre_y = 0, int snake_width = snake_unit::init_node_width, int snake_height = snake_unit::init_node_height, snake_utils::direction_e snake_direction = snake_unit::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK)
			 *
			 * \param name_unit: name of the snake ndoe
			 * \param centre_x: x coordinate of the snake unit
			 * \param centre_y: y coordinate of the snake_unit 
			 * \param snake_width: width of the snake unit
			 * \param snake_height: height of the snake unit
			 * \param snake_direction: direction of the snake unit
			 * \param snake_colour: colour of the snake unit
			 *
			 * SnakeUnit constructor
			 */
			explicit SnakeUnit(std::string name_unit = "Snake Unit", int centre_x = 0, int centre_y = 0, int snake_width = snake_unit::init_node_width, int snake_height = snake_unit::init_node_height, snake_utils::direction_e snake_direction = snake_unit::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK): basic_object::BasicObject(name_unit, centre_x, centre_y, snake_width, snake_height, snake_colour), direction(snake_direction) {
				LOG_INFO(logging::verb_level_e::HIGH, "Constructor of snake unit at (X ", centre_x, ", Y ", centre_y, ")")
			};

			/**
			 * @brief Function: SnakeUnit(const SnakeUnit& copy)
			 *
			 * \param copy: SnakeUnit to copy
			 *
			 * SnakeUnit copy constructor
			 */
			SnakeUnit(const SnakeUnit& copy) : basic_object::BasicObject(copy), direction(copy.direction) {
				LOG_INFO(logging::verb_level_e::HIGH, "Copy constructor of snake unit at (X ", copy.get_x_centre(), ", Y ", copy.get_y_centre(), ")")
			};

			// Get functions
			/**
			 * @brief Function: snake_utils::direction_e get_direction() const
			 *
			 * \return Direction of the SnakeUnit
			 *
			 * Get the direction of the SnakeUnit
			 */
			snake_utils::direction_e get_direction() const;

			// Set functions
			/**
			 * @brief Function: void set_direction(snake_utils::direction_e new_direction)
			 *
			 * \param new_direction: direction the SnakeUnit has to be set to
			 *
			 * Set direction of the SnakeUnit
			 */
			void set_direction(snake_utils::direction_e new_direction);

			/**
			 * @brief Function: void move(const int & speed, const int & win_width, const int & win_height)
			 *
			 * \param speed: speed of the snake unit
			 * \param win_width: width of the window
			 * \param win_height: height of the window
			 *
			 * Move the snake unit according to inputs
			 */
			void move(const int & speed, const int & win_width, const int & win_height);

			// Destructor
			/**
			 * @brief Function: ~SnakeUnit()
			 *
			 * Destructor of SnakeUnit
			 */
			~SnakeUnit();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the SnakeUnit information
			 *
			 * Print SnakeUnit information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void save_data (iofile::File & savefile)
			 *
			 * \param savefile: file to write SnakeUnit information to
			 *
			 * Save the SnakeUnit information
			 */
			void save_data (iofile::File & savefile);

			/**
			 * @brief Function: bool operator== (const snake_unit::SnakeUnit & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload == operator
			 */
			bool operator== (const snake_unit::SnakeUnit & rhs);

			/**
			 * @brief Function: bool operator!= (const snake_unit::SnakeUnit & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload != operator
			 */
			bool operator!= (const snake_unit::SnakeUnit & rhs);

		private:

			/**
			 * @brief direction of the SnakeUnit
			 *
			 */
			snake_utils::direction_e direction;

		protected:
	};

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const snake_unit::SnakeUnit & unit)
	 *
	 * \param os: output stream
	 * \param unit: snake unit to print
	 *
	 * Overload << operator to print window details
	 */
	std::ostream& operator<< (std::ostream& os, const snake_unit::SnakeUnit & unit);


}
/** @} */ // End of SnakeUnitGroup group

#endif // SNAKE_UNIT_H
