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

	/**
	 * @brief Function: int str_to_int(std::string str)
	 *
	 * \param str: string to convert to an integer
	 *
	 * \return integer value of the string
	 *
	 * Convert a string to an integer
	 */
	int str_to_int(std::string str);

	/**
	 * @brief Function: int str_to_bool(std::string str)
	 *
	 * \param str: string to convert to a boolean
	 *
	 * \return boolean value of the string
	 *
	 * Convert a string to a boolean
	 * 0 means false
	 * 1 means true
	 */
	bool str_to_bool(std::string str);

	/**
	 * @brief Function: bool file_exists(std::string filename)
	 *
	 * \param filename: name of the file
	 *
	 * \return boolean value if the file exists
	 *
	 * Check whether file exists
	 * 0 means file doesn't exists
	 * 1 means file exists
	 */
	bool file_exists(std::string filename);

	/**
	 * @brief Function: void file_rename(std::string orig_file, std::string copy_file)
	 *
	 * \param orig_file: original name of the file
	 * \param copy_file: new name of the file
	 *
	 * Rename file
	 */
	void file_rename(std::string orig_file, std::string copy_file);

	/**
	 * @brief Function: void file_delete(std::string filename)
	 *
	 * \param filename: name of the file
	 *
	 * Delete file
	 */
	void file_delete(std::string filename);
}
/** @} */ // End of UtilityGroup group
#endif // UTILITY_H
