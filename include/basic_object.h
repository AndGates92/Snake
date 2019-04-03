#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H
/**
 * @copyright
 * @file basic_object.h
 * @author Andrea Gianarda
 * @date 25th March 2019
 * @brief Basic Object header file
*/

#include "graphics_utils.h"

namespace basic_object {
	/** @defgroup BasicObjectGroup BasicObject Doxygen Group
	 *  Basic Object functions and classes
	 *  @{
	 */

	namespace {
		/**
		 * @brief Node Height
		 *
		 */
		const static int init_obj_height = 10;

		/**
		 * @brief Node Width
		 *
		 */
		const static int init_obj_width = 10;
	}


	class BasicObject {
		public:
			// Constructor
			BasicObject(std::string name_obj = "Unknown", int centre_x = 0, int centre_y = 0, int obj_width = basic_object::init_obj_width, int obj_height = basic_object::init_obj_height, graphics_utils::palette_e obj_colour = graphics_utils::palette_e::BLACK): name(name_obj),  x_centre(centre_x), y_centre(centre_y), width(obj_width), height(obj_height), colour(obj_colour) {
				std::string pretext ("Constructor");
				basic_object::BasicObject::print_info(logging::verb_level_e::LOW, pretext);
			};

			BasicObject(const BasicObject& copy) : x_centre(copy.x_centre), y_centre(copy.y_centre), width(copy.width), height(copy.height), colour(copy.colour) {
				std::string pretext ("Copy Constructor");
				basic_object::BasicObject::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Get functions
			std::string get_name();
			int get_x_centre();
			int get_y_centre();
			int get_width();
			int get_height();
			graphics_utils::palette_e get_colour();

			// Set functions
			void set_name (std::string name_obj);
			void set_x_centre(int new_x_centre);
			void set_y_centre(int new_y_centre);
			void set_width(int new_width);
			void set_height(int new_height);
			void set_colour(graphics_utils::palette_e new_colour);

			template <typename pixel_type>
			void draw(pixel_type * & pixels, int win_width, int win_height);

			// Destructor
			~BasicObject();

			void print_info(logging::verb_level_e verbosity, std::string pretext);

		private:
			std::string name;
			int x_centre;
			int y_centre;
			int width;
			int height;
			graphics_utils::palette_e colour;

		protected:
	};

	/** @} */ // End of BasicObjectGroup group
}

template <typename pixel_type>
void basic_object::BasicObject::draw(pixel_type * & pixels, int win_width, int win_height) {

	pixel_type * colour_ptr = graphics_utils::get_pixel_colour<pixel_type> (this->get_colour());
	int width = this->get_width();
	int height = this->get_height();
	int y_centre = this->get_y_centre();
	int x_centre = this->get_x_centre();

	for (int x_coord = (-(width/2)); x_coord < (width/2); x_coord++) {
		for (int y_coord = (-(height/2)); y_coord < (height/2); y_coord++) {
			int abs_coord = ((y_centre + y_coord) % win_height) * win_width + (x_centre + x_coord);
			for (int colour_idx=0; colour_idx<graphics_utils::no_colours; colour_idx++) {
				pixels[graphics_utils::no_colours * abs_coord + colour_idx] = colour_ptr[colour_idx];
			}
		}
	}

	delete [] colour_ptr;

}

#endif // BASIC_OBJECT_H
