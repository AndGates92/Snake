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
#include "snake_utils.h"
#include "colours.h"

/** @defgroup SnakeNodeGroup Snake Node Doxygen Group
 *  Snake Node functions and classes
 *  @{
 */
namespace snake_node {

	namespace {
		/**
		 * @brief Initial speed
		 *
		 */
		const static snake_utils::direction_e init_direction = snake_utils::direction_e::RIGHT;

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

	/**
	 * @brief SnakeUnit class
	 *
	 */
	class SnakeUnit : public basic_object::BasicObject {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeUnit(std::string name_unit = "Snake Unit", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_utils::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK)
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
			SnakeUnit(std::string name_unit = "Snake Unit", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_utils::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK): basic_object::BasicObject(name_unit, centre_x, centre_y, snake_width, snake_height, snake_colour), direction(snake_direction) {
				std::string pretext ("Constructor");
				snake_node::SnakeUnit::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: SnakeUnit(const SnakeUnit& copy)
			 *
			 * \param copy: SnakeUnit to copy
			 *
			 * SnakeUnit copy constructor
			 */
			SnakeUnit(const SnakeUnit& copy) : basic_object::BasicObject(copy), direction(copy.direction) {
				std::string pretext ("Copy Constructor");
				snake_node::SnakeUnit::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Get functions
			/**
			 * @brief Function: snake_utils::direction_e get_direction()
			 *
			 * \return Direction of the SnakeUnit
			 *
			 * Get the direction of the SnakeUnit
			 */
			snake_utils::direction_e get_direction();

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

		private:

			/**
			 * @brief direction of the SnakeUnit
			 *
			 */
			snake_utils::direction_e direction;

		protected:
	};

	/**
	 * @brief SnakeNode class
	 *
	 */
	class SnakeNode : public basic_obj_node::BasicObjNode<SnakeNode>, public SnakeUnit {
		public:
			// Constructor
			/**
			 * @brief Function: SnakeNode(std::string name_node = "Snake Node", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_utils::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK)
			 *
			 * \param name_node: name of the snake ndoe
			 * \param centre_x: x coordinate of the snake node
			 * \param centre_y: y coordinate of the snake_node 
			 * \param snake_width: width of the snake node
			 * \param snake_height: height of the snake node
			 * \param snake_direction: direction of the snake node
			 * \param snake_colour: colour of the snake node
			 *
			 * SnakeNode constructor
			 */
			SnakeNode(std::string name_node = "Snake Node", int centre_x = 0, int centre_y = 0, int snake_width = snake_node::init_node_width, int snake_height = snake_node::init_node_height, snake_utils::direction_e snake_direction = snake_node::init_direction, colours::palette_e snake_colour = colours::palette_e::BLACK): basic_obj_node::BasicObjNode<SnakeNode>(), SnakeUnit(name_node, centre_x, centre_y, snake_width, snake_height, snake_direction, snake_colour) {
				std::string pretext ("Snake Node Constructor");
				snake_node::SnakeNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: SnakeNode(const SnakeNode& copy)
			 *
			 * \param copy: SnakeNode to copy
			 *
			 * SnakeNode copy constructor
			 */
			SnakeNode(const SnakeNode& copy) : basic_obj_node::BasicObjNode<SnakeNode>(copy), SnakeUnit(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~SnakeNode()
			 *
			 * Destructor of SnakeNode
			 */
			~SnakeNode();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the SnakeNode information
			 *
			 * Print SnakeNode information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
	};
}
/** @} */ // End of SnakeNodeGroup group

#endif // SNAKE_NODE_H
