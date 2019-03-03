#ifndef SNAKE_UNIT_H
#define SNAKE_UNIT_H
/**
 * @copyright
 * @file file.h
 * @author Andrea Gianarda
 * @date 06th of February 2019
 * @brief File handling header file
*/

#include <fstream>

namespace snake_unit {

	/** @defgroup FileGroup File Doxygen Group
	 *  File functions and classes
	 *  @{
	 */
	/**
	 * @brief Initial speed
	 *
	 */
	const static int init_speed = 2;


	class SnakeUnit {
		public:
			// Constructor
			SnakeUnit(int centre_x = 0, int centre_y = 0, int speed = snake_unit::init_speed): x_centre(centre_x), y_centre(centre_y), speed(speed) {
			};

			// Destructor
			~SnakeUnit();

		private:
			int x_centre;
			int y_centre;
			int speed;

		protected:
	};
	/** @} */ // End of FileGroup group
}

#endif // SNAKE_UNIT_H
