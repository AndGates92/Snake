#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H
/**
 * @copyright
 * @file basic_object.h
 * @author Andrea Gianarda
 * @date 25th March 2019
 * @brief Basic Object header file
*/

#include "colours.h"
#include "file.h"

/** @defgroup BasicObjectGroup BasicObject Doxygen Group
 *  Basic Object functions and classes
 *  @{
 */
namespace basic_object {
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
			/**
			 * @brief Function: BasicObject(std::string type_obj = "Unknown", int centre_x = 0, int centre_y = 0, int obj_width = basic_object::init_obj_width, int obj_height = basic_object::init_obj_height, colours::palette_e obj_colour = colours::palette_e::BLACK)
			 *
			 * \param type_obj: object type
			 * \param centre_x: x coordinate of the object
			 * \param centre_y: y coordinate of the object
			 * \param obj_width: width of the object
			 * \param obj_height: height of the object
			 * \param obj_colour: colour of the object
			 *
			 * BasicObject constructor
			 */
			BasicObject(std::string type_obj = "Unknown", int centre_x = 0, int centre_y = 0, int obj_width = basic_object::init_obj_width, int obj_height = basic_object::init_obj_height, colours::palette_e obj_colour = colours::palette_e::BLACK): type(type_obj),  x_centre(centre_x), y_centre(centre_y), width(obj_width), height(obj_height), colour(obj_colour) {
				std::string pretext ("Constructor");
				basic_object::BasicObject::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: BasicObject(const BasicObject& copy)
			 *
			 * \param copy: BasicObject to copy
			 *
			 * BasicObject copy constructor
			 */
			BasicObject(const BasicObject& copy) : x_centre(copy.x_centre), y_centre(copy.y_centre), width(copy.width), height(copy.height), colour(copy.colour) {
				std::string pretext ("Copy Constructor");
				basic_object::BasicObject::print_info(logging::verb_level_e::LOW, pretext);
			};

			// Get functions
			/**
			 * @brief Function: std::string get_type()
			 *
			 * \return object type
			 *
			 * Get type of the BasicObject
			 */
			std::string get_type();
			/**
			 * @brief Function: int get_x_centre()
			 *
			 * \return x coordinate of the object
			 *
			 * Get x coordinate of the BasicObject
			 */
			int get_x_centre();
			/**
			 * @brief Function: int get_y_centre()
			 *
			 * \return y coordinate of the object
			 *
			 * Get y coordinate of the BasicObject
			 */
			int get_y_centre();
			/**
			 * @brief Function: int get_width()
			 *
			 * \return width of the object
			 *
			 * Get width of the BasicObject
			 */
			int get_width();
			/**
			 * @brief Function: int get_height()
			 *
			 * \return height of the object
			 *
			 * Get height of the BasicObject
			 */
			int get_height();
			/**
			 * @brief Function: int get_colour()
			 *
			 * \return colour of the object
			 *
			 * Get colour of the BasicObject
			 */
			colours::palette_e get_colour();

			// Set functions
			/**
			 * @brief Function: void set_colour(std::string type_obj)
			 *
			 * \param type_obj: new type of the object
			 *
			 * Set type of the BasicObject
			 */
			void set_type (std::string type_obj);
			/**
			 * @brief Function: void set_x_centre(int new_x_centre)
			 *
			 * \param new_x_centre: new x coordinate of the object
			 *
			 * Set x coordinate of the BasicObject
			 */
			void set_x_centre(int new_x_centre);
			/**
			 * @brief Function: void set_y_centre(int new_y_centre)
			 *
			 * \param new_y_centre: new y coordinate of the object
			 *
			 * Set y coordinate of the BasicObject
			 */
			void set_y_centre(int new_y_centre);
			/**
			 * @brief Function: void set_width(int new_width)
			 *
			 * \param new_width: new width of the object
			 *
			 * Set y coordinate of the BasicObject
			 */
			void set_width(int new_width);
			/**
			 * @brief Function: void set_height(int new_height)
			 *
			 * \param new_height: new height of the object
			 *
			 * Set height of the BasicObject
			 */
			void set_height(int new_height);
			/**
			 * @brief Function: void set_colour(colours::palette_e new_colour)
			 *
			 * \param new_colour: new colour of the object
			 *
			 * Set colour of the BasicObject
			 */
			void set_colour(colours::palette_e new_colour);

			/**
			 * @brief Function: void draw(pixel_type * & pixels, const int & win_width, const int & win_height)
			 *
			 * \param pixels: array of pixels to draw
			 * \param win_width: width of the window
			 * \param win_height: height of the window
			 *
			 * Draw the BasicObject onto the window
			 */
			template <typename pixel_type>
			void draw(pixel_type * & pixels, const int & win_width, const int & win_height);

			// Destructor
			/**
			 * @brief Function: ~BasicObject()
			 *
			 * Destructor of BasicObject
			 */
			~BasicObject();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the BasicObject information
			 *
			 * Print BasicObject information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void save_data (iofile::File & savefile)
			 *
			 * \param savefile: file to write BasicObject information to
			 *
			 * Save the BasicObject information
			 */
			void save_data (iofile::File & savefile);

		private:
			/**
			 * @brief Type
			 *
			 */
			std::string type;
			/**
			 * @brief X coordinate
			 *
			 */
			int x_centre;
			/**
			 * @brief Y coordinate
			 *
			 */
			int y_centre;
			/**
			 * @brief Width
			 *
			 */
			int width;
			/**
			 * @brief Height
			 *
			 */
			int height;
			/**
			 * @brief Colour
			 *
			 */
			colours::palette_e colour;

		protected:
	};

}
/** @} */ // End of BasicObjectGroup group

template <typename pixel_type>
void basic_object::BasicObject::draw(pixel_type * & pixels, const int & win_width, const int & win_height) {

	pixel_type * colour_ptr = colours::get_pixel_colour<pixel_type> (this->get_colour());
	int width = this->get_width();
	int height = this->get_height();
	int y_centre = this->get_y_centre();
	int x_centre = this->get_x_centre();

	for (int x_coord = (-(width/2)); x_coord < (width/2); x_coord++) {
		int x_abs = (x_centre + x_coord);
		// Deal with case where snake appears on the other side of the screen
		if (x_abs < 0) {
			x_abs += win_width;
		}
		x_abs = x_abs % win_width;
		ASSERT((x_abs >=0) & (x_abs < win_width));
		for (int y_coord = (-(height/2)); y_coord < (height/2); y_coord++) {
			int y_abs = (y_centre + y_coord);
			// Deal with case where snake appears on the other side of the screen
			if (y_abs < 0) {
				y_abs += win_height;
			}
			y_abs = y_abs % win_height;
			ASSERT((y_abs >=0) & (y_abs < win_height));
			int abs_coord = y_abs * win_width + x_abs;
			for (int colour_idx=0; colour_idx<colours::no_colours; colour_idx++) {
				pixels[colours::no_colours * abs_coord + colour_idx] = colour_ptr[colour_idx];
			}
		}
	}

	delete [] colour_ptr;

}

#endif // BASIC_OBJECT_H
