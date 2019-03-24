#ifndef OBSTACLE_H
#define OBSTACLE_H
/**
 * @copyright
 * @file obstacle.h
 * @author Andrea Gianarda
 * @date 22nd March 2019
 * @brief Obstacle header file
*/

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


	class Obstacle {
		public:
			// Constructor
			Obstacle(int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, graphics_utils::palette_e obs_colour = graphics_utils::palette_e::BLACK): x_centre(centre_x), y_centre(centre_y), width(obs_width), height(obs_height), colour(obs_colour) {
				std::string pretext ("Obstacle Constructor");
				obstacle::Obstacle::print_info(logging::verb_level_e::LOW, pretext);
			};

			Obstacle(const Obstacle& copy) : x_centre(copy.x_centre), y_centre(copy.y_centre), width(copy.width), height(copy.height), colour(copy.colour) {
				std::string pretext ("Obstacle Copy Constructor");
				obstacle::Obstacle::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Get functions
			int get_x_centre();
			int get_y_centre();
			int get_width();
			int get_height();
			graphics_utils::palette_e get_colour();

			// Set functions
			void set_x_centre(int new_x_centre);
			void set_y_centre(int new_y_centre);
			void set_width(int new_width);
			void set_height(int new_height);
			void set_colour(graphics_utils::palette_e new_colour);

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int & win_width);

			// Destructor
			~Obstacle();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			int x_centre;
			int y_centre;
			int width;
			int height;
			graphics_utils::palette_e colour;

		protected:
	};

	class ObstacleNode : public Obstacle {
		public:
			// Constructor
			ObstacleNode(int centre_x = 0, int centre_y = 0, int obs_width = obstacle::init_obs_width, int obs_height = obstacle::init_obs_height, graphics_utils::palette_e obs_colour = graphics_utils::palette_e::BLACK): Obstacle(centre_x, centre_y, obs_width, obs_height, obs_colour), prev(nullptr), next(nullptr) {
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

	pixel_type * colour_ptr = graphics_utils::get_pixel_colour<pixel_type> (this->colour);

	for (int x_coord = (-(this->width/2)); x_coord < (this->width/2); x_coord++) {
		for (int y_coord = (-(this->height/2)); y_coord < (this->height/2); y_coord++) {
			int abs_coord = (this->y_centre + y_coord) * win_width + (x_centre + x_coord);
			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * abs_coord + colour_idx] = colour_ptr[colour_idx];
			}
		}
	}

	delete [] colour_ptr;

}

#endif // OBSTACLE_H
