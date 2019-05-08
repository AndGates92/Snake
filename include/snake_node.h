#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H
/**
 * @copyright
 * @file snake_node.h
 * @author Andrea Gianarda
 * @date 03rd of March 2019
 * @brief Snake node header file
*/

#include "basic_object.h"
#include "basic_obj_node.h"
#include "colours.h"

namespace snake_node {

	/** @defgroup SnakeNodeGroup Snake Node Doxygen Group
	 *  Snake Node functions and classes
	 *  @{
	 */

	/**
	 * @brief Directions
	 *
	 */
	typedef enum class direction_type {
		UP,
		DOWN,
		LEFT,
		RIGHT
	} direction_e;

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, game_menu::direction_e direction)
	 *
	 * \param os: output stream
	 * \param direction: direction to be printed
	 *
	 * Overload << operator to print direction 
	 */
	std::ostream& operator<< (std::ostream& os, snake_node::direction_e direction);

	namespace {
		/**
		 * @brief Initial speed
		 *
		 */
		const static snake_node::direction_e init_direction = snake_node::direction_e::RIGHT;

		/**
		 * @brief Node Height
		 *
		 */
		const static int init_node_height = 10;

		/**
		 * @brief Node Width
		 *
		 */
		const static int init_node_width = 10;
	}

	class SnakeUnit : public basic_object::BasicObject {
		public:
			// Constructor
			SnakeUnit(std::string name_unit = "Snake Unit", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_node::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK): basic_object::BasicObject(name_unit, centre_x, centre_y, snake_width, snake_height, snake_colour), direction(snake_direction) {
				std::string pretext ("Constructor");
				snake_node::SnakeUnit::print_info(logging::verb_level_e::LOW, pretext);
			};

			SnakeUnit(const SnakeUnit& copy) : basic_object::BasicObject(copy), direction(copy.direction) {
				std::string pretext ("Copy Constructor");
				snake_node::SnakeUnit::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Get functions
			snake_node::direction_e get_direction();

			// Set functions
			void set_direction(snake_node::direction_e new_direction);

			void move(const int & speed, const int & win_width, const int & win_height);

			// Destructor
			~SnakeUnit();

			void print_info(logging::verb_level_e verbosity, std::string pretext);
			void save_data (iofile::File & savefile);

		private:
			snake_node::direction_e direction;

		protected:
	};

	class SnakeNode : public basic_obj_node::BasicObjNode<SnakeNode>, public SnakeUnit {
		public:
			// Constructor
			SnakeNode(std::string name_node = "Snake Node", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_node::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK): basic_obj_node::BasicObjNode<SnakeNode>(), SnakeUnit(name_node, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour) {
				std::string pretext ("Snake Node Constructor");
				snake_node::SnakeNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			SnakeNode(const SnakeNode& copy) : basic_obj_node::BasicObjNode<SnakeNode>(copy), SnakeUnit(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~SnakeNode();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
	};
	/** @} */ // End of SnakeNodeGroup group
}
#endif // SNAKE_NODE_H
