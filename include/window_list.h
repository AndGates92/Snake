#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file window_list.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window List header file
*/

#include "window_node.h"

namespace window_list {
	/** @defgroup WindowListGroup Window List Doxygen Group
	 *  Window List functions and classes
	 *  @{
	 */

	template <typename entry_e>
	class WindowList {
		public:
			// Constructor
			WindowList();

			// Destructor
			~WindowList();

		protected:

		private:
			WindowNode * head;
	};
	/** @} */ // End of WindowListGroup group
}

template <typename entry_e>
window_list::WindowList<entry_e>::~WindowList() {

	LOG_INFO(log::verb_level_e::HIGH, "Window node destroyed");
	delete[] node;

}

#endif // WINDOW_LIST_H
