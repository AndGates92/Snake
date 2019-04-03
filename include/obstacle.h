#ifndef OBSTACLE_H
#define OBSTACLE_H
/**
 * @copyright
 * @file obstacle.h
 * @author Andrea Gianarda
 * @date 22nd March 2019
 * @brief Obstacle header file
*/

#include "basic_object.h"
#include "basic_obj_node.h"
#include "graphics_utils.h"

namespace obstacle {
	/** @defgroup ObstacleGroup Obstacle Doxygen Group
	 *  Obstacle functions and classes
	 *  @{
	 */

	namespace {
		/**
		 * @brief Node Height
		 *
		 */
		const static int init_obs_height = 10;

		/**
		 * @brief Node Width
		 *
		 */
		const static int init_obs_width = 10;
	}


	class Obstacle : public basic_object::BasicObject {
		public:
			// Constructor
			Obstacle(std::string name_obs = "Obstacle", int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, graphics_utils::palette_e obs_colour = graphics_utils::palette_e::BLACK): basic_object::BasicObject(name_obs, centre_x, centre_y, obs_width, obs_height, obs_colour) {
				std::string pretext ("Constructor");
				obstacle::Obstacle::print_info(logging::verb_level_e::LOW, pretext);
			};

			Obstacle(const Obstacle& copy) : basic_object::BasicObject(copy) {
				std::string pretext ("Copy Constructor");
				obstacle::Obstacle::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Destructor
			~Obstacle();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:

		protected:
	};

	class ObstacleNode : public basic_obj_node::BasicObjNode<ObstacleNode>, public Obstacle {
		public:
			// Constructor
			ObstacleNode(std::string name_obs = "Obstacle Node", int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, graphics_utils::palette_e obs_colour = graphics_utils::palette_e::BLACK): basic_obj_node::BasicObjNode<ObstacleNode>(), Obstacle(name_obs, centre_x, centre_y, obs_width, obs_height, obs_colour) {
				std::string pretext ("Constructor");
				obstacle::ObstacleNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			ObstacleNode(const ObstacleNode& copy) : basic_obj_node::BasicObjNode<ObstacleNode>(copy), Obstacle(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~ObstacleNode();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
	};
	/** @} */ // End of ObstacleGroup group
}

#endif // OBSTACLE_H
