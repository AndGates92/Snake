#ifndef IS_MATCHING_H
#define IS_MATCHING_H
/**
 * @copyright
 * @file is_matching.h
 * @author Andrea Gianarda
 * @date 19th of August 2019
 * @brief is_matching header file
*/

#include "basic_obj_list.h"

/** @defgroup IsMatchingGroup Window List Doxygen Group
 *  Is matching functions and classes
 *  @{
 */
namespace is_matching {
	/**
	 * @brief WindowList class
	 *
	 */
	template <class element_type, class class_type>
	class IsMatching {
		public:
			// Constructor
			/**
			 * @brief Function: IsMatching(element_type element)
			 *
			 * \param name_win: name of the WindowList
			 *
			 * IsMatching constructor
			 */
			IsMatching(element_type element): reference(element) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			bool operator()(class_type cl) const {
				// temporary node
				int curr_win_id = cl->get_win_id();

				LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", win_id);

				// Current ID matches searched ID
				return (curr_win_id == reference);
			}

		protected:

		private:
			element_type reference;
	}
}


