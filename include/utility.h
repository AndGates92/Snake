#ifndef UTILITY_H
#define UTILITY_H
/**
 * @copyright
 * @file utility.h
 * @author Andrea Gianarda
 * @date 05th of February 2019
 * @brief Utility handling header file
*/

/** @defgroup UtilityGroup Utility Doxygen Group
 *  Functions and defines concerning utility
 *  @{
 */
/**
 * @brief STRINGIFY_EXPR(x)
 *
 * \param x : argument to stringify
 *
 * Stringify input argumet
 *
 */
#define STRINGIFY_EXPR(x) #x

/**
 * @brief STRINGIFY(x)
 *
 * \param x : argument to stringify
 *
 * Evaluate input argument and pass it on to STRINGIFY macro
 *
 */
#define STRINGIFY(x) STRINGIFY_EXPR(x)

namespace utility {

	int str_to_int (std::string str);

	bool file_exists (std::string filename);

	void file_rename (std::string orig_file, std::string copy_file);
	void file_delete (std::string filename);
}
/** @} */ // End of UtilityGroup group
#endif // UTILITY_H
