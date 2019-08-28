#ifndef IS_MATCHING_H
#define IS_MATCHING_H
/**
 * @copyright
 * @file is_matching.h
 * @author Andrea Gianarda
 * @date 19th of August 2019
 * @brief is_matching header file
*/

#include "logging.h"

/** @defgroup IsMatchingGroup Doxygen Group
 *  Is matching functions and classes
 *  @{
 */
namespace is_matching {
	/**
	 * @brief IsMatching class
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
			IsMatching(element_type element): reference_id(element) { LOG_INFO(logging::verb_level_e::LOW, "Constructor") };

			/**
			 * @brief Function: bool operator()(class_type cl) const
			 *
			 * \param unit: class to match
			 *
			 * \return whether the reference_id and the current class ID match
			 *
			 * Determine whether the ID fo the current and refrence clas match 
			 */
			bool operator()(class_type cl) const;

		protected:

		private:
			element_type reference_id;
	};
}
/** @} */ // End of IsMatchingGroup group

template <class element_type, class class_type>
bool is_matching::IsMatching<element_type, class_type>::operator()(class_type cl) const {
	element_type curr_win_id = cl.get_win_id();

	LOG_INFO(logging::verb_level_e::DEBUG,"[New search by windows ID] Window ID: current ", curr_win_id, " searched ", this->reference_id);

	// Current ID matches searched ID
	return (curr_win_id == this->reference_id);
}

#endif // IS_MATCHING_H
