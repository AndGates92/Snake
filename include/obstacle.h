#ifndef OBSTACLE_H
#define OBSTACLE_H
/**
 * @copyright
 * @file obstacle.h
 * @author Andrea Gianarda
 * @date 22nd March 2019
 * @brief Obstacle header file
*/

#include "colours.h"
#include "basic_object.h"

/** @defgroup ObstacleGroup Obstacle Doxygen Group
 *  Obstacle functions and classes
 *  @{
 */
namespace obstacle {
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

	/**
	 * @brief Obstacle class
	 *
	 */
	class Obstacle : public basic_object::BasicObject {
		public:
			// Constructor
			/**
			 * @brief Function: Obstacle(std::string type_obs = "Obstacle", int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, colours::palette_e obs_colour = colours::palette_e::BLACK)
			 *
			 * \param type_obs: name of the obstacle
			 * \param centre_x: x coordinate of the obstacle
			 * \param centre_y: y coordinate of the obstacle
			 * \param obs_width: obstacle width
			 * \param obs_height: obstacle height
			 * \param obs_colour: obstacle colour
			 *
			 * Obstacle constructor
			 */
			explicit Obstacle(std::string type_obs = "Obstacle", int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, colours::palette_e obs_colour = colours::palette_e::BLACK): basic_object::BasicObject(type_obs, centre_x, centre_y, obs_width, obs_height, obs_colour) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Constructor of obstacle at (X ", centre_x, ", Y ", centre_y, ")")
			};

			/**
			 * @brief Function: Obstacle(const Obstacle& copy)
			 *
			 * \param copy: Obstacle to copy
			 *
			 * Obstacle copy constructor
			 */
			Obstacle(const Obstacle& copy) : basic_object::BasicObject(copy) {
				LOG_INFO(logging::verb_level_e::DEBUG, "Copy constructor of obstacle at (X ", copy.get_x_centre(), ", Y ", copy.get_y_centre(), ")")
			};

			// Destructor
			/**
			 * @brief Function: ~Obstacle()
			 *
			 * Destructor of Obstacle
			 */
			~Obstacle();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the Obstacle information
			 *
			 * Print Obstacle information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:

		protected:
	};

}
/** @} */ // End of ObstacleGroup group

#endif // OBSTACLE_H
