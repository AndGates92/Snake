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

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int & win_width);

			// Destructor
			~Obstacle();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:

		protected:
	};

	class ObstacleNode : public Obstacle {
		public:
			// Constructor
			ObstacleNode(std::string name_obs = "Obstacle", int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, graphics_utils::palette_e obs_colour = graphics_utils::palette_e::BLACK): Obstacle(name_obs, centre_x, centre_y, obs_width, obs_height, obs_colour), prev(nullptr), next(nullptr) {
				std::string pretext ("Obstacle Node Constructor");
				obstacle::ObstacleNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			ObstacleNode(const ObstacleNode& copy) : Obstacle(copy), prev(copy.prev), next(copy.next) { LOG_INFO(logging::verb_level_e::LOW, "Obstacle node copy contructor") };

			// Destructor
			~ObstacleNode();

			// Get functions
			ObstacleNode * & get_next();
			ObstacleNode * & get_prev();

			// Set functions
			void set_next(ObstacleNode * next_ptr);
			void set_prev(ObstacleNode * prev_ptr);

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		protected:

		private:
			ObstacleNode * prev;
			ObstacleNode * next;
	};
	/** @} */ // End of ObstacleGroup group
}

template <typename pixel_type>
void obstacle::Obstacle::draw(pixel_type * & pixels, int & win_width) {

	pixel_type * colour_ptr = graphics_utils::get_pixel_colour<pixel_type> (this->get_colour());
	int width = this->get_width();
	int height = this->get_height();
	int y_centre = this->get_y_centre();
	int x_centre = this->get_x_centre();

	for (int x_coord = (-(width/2)); x_coord < (width/2); x_coord++) {
		for (int y_coord = (-(height/2)); y_coord < (height/2); y_coord++) {
			int abs_coord = (y_centre + y_coord) * win_width + (x_centre + x_coord);
			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * abs_coord + colour_idx] = colour_ptr[colour_idx];
			}
		}
	}

	delete [] colour_ptr;

}

#endif // OBSTACLE_H
