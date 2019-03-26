#ifndef OBSTACLE_LIST_H
#define OBSTACLE_LIST_H
/**
 * @copyright
 * @file obstacle_list.h
 * @author Andrea Gianarda
 * @date 24th March 2019
 * @brief Obstacle List header file
*/

#include "graphics_utils.h"
#include "obstacle.h"

namespace obstacle_list {
	/** @defgroup ObstacleListGroup Obstacle List Doxygen Group
	 *  Obstacle List functions and classes
	 *  @{
	 */

	class ObstacleList {
		public:
			// Constructor
			ObstacleList(): head(nullptr) { LOG_INFO(logging::verb_level_e::LOW, "Obstacle list contructed") };

			ObstacleList(const ObstacleList& copy): head(copy.head) { LOG_INFO(logging::verb_level_e::LOW, "Obstacle list copy contructor") };

			// Destructor
			~ObstacleList();

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int & win_width);

			void add_node(std::string name_obs, int centre_x, int centre_y, int obstacle_width, int obstacle_height, graphics_utils::palette_e obstacle_colour);
			void remove_node(obstacle::ObstacleNode * & node);

			void print_info(logging::verb_level_e verbosity, std::string pretext);

			obstacle::ObstacleNode * get_head();

		protected:

		private:
			obstacle::ObstacleNode * head;
	};
	/** @} */ // End of ObstacleListGroup group
}

template <typename pixel_type>
void obstacle_list::ObstacleList::draw(pixel_type * & pixels, int & win_width) {
	obstacle::ObstacleNode * obstacle_node = this->head;

	while (obstacle_node != nullptr) {

		obstacle_node->draw(pixels, win_width);

		obstacle_node = obstacle_node->get_next();

	}

}

#endif // OBSTACLE_LIST_H
