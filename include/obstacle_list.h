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

namespace obstacle_list {
	/** @defgroup ObstacleListGroup Obstacle List Doxygen Group
	 *  Obstacle List functions and classes
	 *  @{
	 */

	class ObstacleList : public basic_obj_list::BasicObjList<obstacle::ObstacleNode> {
		public:
			// Constructor
			ObstacleList(std::string name_obs = "Obstacle List"): basic_obj_list::BasicObjList<obstacle::ObstacleNode>(name_obs) { LOG_INFO(logging::verb_level_e::LOW, "Contructed") };

			ObstacleList(const ObstacleList& copy): basic_obj_list::BasicObjList<obstacle::ObstacleNode>(copy) { LOG_INFO(logging::verb_level_e::LOW, "Copy contructor") };

			// Destructor
			~ObstacleList();

			void add_node(int centre_x, int centre_y, int ostacle_width, int ostacle_height, colours::palette_e ostacle_colour);

		protected:

		private:
	};
	/** @} */ // End of ObstacleListGroup group
}



#endif // OBSTACLE_LIST_H
