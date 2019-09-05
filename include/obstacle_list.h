#ifndef OBSTACLE_LIST_H
#define OBSTACLE_LIST_H
/**
 * @copyright
 * @file obstacle_list.h
 * @author Andrea Gianarda
 * @date 24th March 2019
 * @brief Obstacle List header file
*/

#include "colours.h"
#include "basic_obj_list.h"
#include "obstacle.h"

/** @defgroup ObstacleListGroup Obstacle List Doxygen Group
 *  Obstacle List functions and classes
 *  @{
 */
namespace obstacle_list {
	/**
	 * @brief ObstacleList class
	 *
	 */
	class ObstacleList : public basic_obj_list::BasicObjList<obstacle::Obstacle> {
		public:
			// Constructor
			/**
			 * @brief Function: ObstacleList(std::string window_title = "")
			 *
			 * \param name_obs: Name of the obstacle list
			 *
			 * ObstacleList constructor
			 */
			explicit ObstacleList(std::string name_obs = "Obstacle List"): basic_obj_list::BasicObjList<obstacle::Obstacle>(name_obs) { LOG_INFO(logging::verb_level_e::LOW, "Contructed") };

			/**
			 * @brief Function: ObstacleList(const ObstacleList& copy)
			 *
			 * \param copy: ObstacleList to copy
			 *
			 * ObstacleList copy constructor
			 */
			ObstacleList(const ObstacleList& copy): basic_obj_list::BasicObjList<obstacle::Obstacle>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			/**
			 * @brief Function: ~ObstacleList()
			 *
			 * Destructor of ObstacleList
			 */
			~ObstacleList();

			/**
			 * @brief Function: void add_element(int centre_x, int centre_y, int obstacle_width, int ovstacle_height, colours::palette_e obstacle_colour)
			 *
			 * \param centre_x: x coordinate of the obstacle
			 * \param centre_y: y coordinate of the obstacle
			 * \param obstacle_width: obstacle width
			 * \param obstacle_height: obstacle height
			 * \param obstacle_colour: obstacle colour
			 *
			 * ObstacleList constructor
			 */
			void add_element(int centre_x, int centre_y, int obstacle_width, int obstacle_height, colours::palette_e obstacle_colour);

		protected:

		private:
	};
}
/** @} */ // End of ObstacleListGroup group

#endif // OBSTACLE_LIST_H
