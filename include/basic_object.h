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

	/**
	 * @brief BasicObject class
	 *
	 */
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
			explicit BasicObject(std::string type_obj = "Unknown", int centre_x = 0, int centre_y = 0, int obj_width = basic_object::init_obj_width, int obj_height = basic_object::init_obj_height, colours::palette_e obj_colour = colours::palette_e::BLACK): type(type_obj),  x_centre(centre_x), y_centre(centre_y), width(obj_width), height(obj_height), colour(obj_colour) {
				LOG_INFO(logging::verb_level_e::HIGH, "Constructor of basic object ", type_obj)
			};

			/**
			 * @brief Function: BasicObject(const BasicObject& copy)
			 *
			 * \param copy: BasicObject to copy
			 *
			 * BasicObject copy constructor
			 */
			BasicObject(const BasicObject& copy) : type(copy.type), x_centre(copy.x_centre), y_centre(copy.y_centre), width(copy.width), height(copy.height), colour(copy.colour) {
				LOG_INFO(logging::verb_level_e::HIGH, "Copy constructor of basic object ", copy.type)
			};

			// Get functions
			/**
			 * @brief Function: std::string get_type() const
			 *
			 * \return object type
			 *
			 * Get type of the BasicObject
			 */
			std::string get_type() const;
			/**
			 * @brief Function: int get_x_centre() const
			 *
			 * \return x coordinate of the object
			 *
			 * Get x coordinate of the BasicObject
			 */
			int get_x_centre() const;
			/**
			 * @brief Function: int get_y_centre() const
			 *
			 * \return y coordinate of the object
			 *
			 * Get y coordinate of the BasicObject
			 */
			int get_y_centre() const;
			/**
			 * @brief Function: int get_width() const
			 *
			 * \return width of the object
			 *
			 * Get width of the BasicObject
			 */
			int get_width() const;
			/**
			 * @brief Function: int get_height() const
			 *
			 * \return height of the object
			 *
			 * Get height of the BasicObject
			 */
			int get_height() const;
			/**
			 * @brief Function: int get_colour() const
			 *
			 * \return colour of the object
			 *
			 * Get colour of the BasicObject
			 */
			colours::palette_e get_colour() const;

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
			 * @brief Function: virtual ~BasicObject()
			 *
			 * Destructor of BasicObject
			 */
			virtual ~BasicObject();

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

			/**
			 * @brief Function: bool operator== (const basic_object::BasicObject & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload == operator
			 */
			bool operator== (const basic_object::BasicObject & rhs);

			/**
			 * @brief Function: bool operator!= (const basic_object::BasicObject & rhs)
			 *
			 * \param rhs: base object to compare with
			 *
			 * Overload != operator
			 */
			bool operator!= (const basic_object::BasicObject & rhs);

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

	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, const basic_object::BasicObject & object)
	 *
	 * \param os: output stream
	 * \param object: object to print
	 *
	 * Overload << operator to print basic object details
	 */
	std::ostream& operator<< (std::ostream& os, const basic_object::BasicObject & object);

}


/** @} */ // End of BasicObjectGroup group

template <typename pixel_type>
void basic_object::BasicObject::draw(pixel_type * & pixels, const int & win_width, const int & win_height) {

	const pixel_type * colour_ptr = colours::get_pixel_colour<pixel_type> (this->get_colour());
	const int width = this->get_width();
	const int height = this->get_height();
	const int y_centre = this->get_y_centre();
	const int x_centre = this->get_x_centre();

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
