#ifndef LOG_H
#define LOG_H
/**
 * @copyright
 * @file logging.h
 * @author Andrea Gianarda
 * @date 04th of February 2019
 * @brief Log handling header file
*/

#include <iostream>
#include <sstream>
#include <mutex>

#include "file.h"
#include "utility.h"
#include "custom_exception.h"

/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE snake.log
#endif

/**
 * @brief Default verbosity level
 *
 */
#if !defined(VERBOSITY)
	#define VERBOSITY MEDIUM
#endif

/**
 * @brief LOG_INFO(VERBOSITY, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param ... :       variable number of arguments to provide to log_info
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define LOG_INFO(VERBOSITY, ...)\
	logging::log_info(VERBOSITY, "File ", __FILE__, " at line ", __LINE__, ": ", __VA_ARGS__, "\n");

/**
 * @brief LOG_ERROR(...)
 *
 * \param ... :       variable number of arguments to provide to log_error
 *
 * Print an error message to std::cerr
 */
#define LOG_ERROR(...)\
	logging::log_error("File ", __FILE__, " at line ", __LINE__, ": ", __VA_ARGS__, "\n");

/**
 * @brief ASSERT(EXPR)
 *
 * \param EXPR : expression to assert
 *
 * Assert the expression and if it fails, an error message is printed to stderr and the program exits with EXIT_FAILURE status
 */
#ifdef ENABLE_ASSERTIONS
#define ASSERT(EXPR)\
	if (!(EXPR)) {\
		LOG_ERROR("ASSERTION FAILED (", STRINGIFY(EXPR), ")");\
	}
#else
#define ASSERT(EXPR)\
	if (!(EXPR)) {\
		LOG_INFO(logging::verb_level_e::ZERO,"ASSERTION FAILED (", STRINGIFY(EXPR), ")");\
	}
#endif // ENABLE_ASSERTIONS

/** @defgroup LogGroup Log Doxygen Group
 *  Functions and defines logging progress
 *  @{
 */
namespace logging {

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class verb_level_list {
		ZERO,   /**< Always printed */
		LOW,    /**< Low level */
		MEDIUM, /**< Medium level */
		HIGH,   /**< High level */
		DEBUG   /**< Debug level */
	} verb_level_e;

	/** 
	 * @brief Function: void log_error (err_type... err)
	 *
	 * \param err:        string to print using std::cerr
	 *
	 * Log errors to a error stream
	 */
	template <typename... err_type>
	void log_error (err_type... err);

	/** 
	 * @brief Function: void log_info (verb_lvl_e verbosity, info_type&... info)
	 *
	 * \param verbosity:   specify the minimum verbosity level required to print a message
	 * \param info:        string to print using std::cout
	 *
	 * Log information to a logfile if desired verbosity level is higher than the requested one
	 */
	template <typename... info_type>
	void log_info (logging::verb_level_e verbosity, info_type... info);

	/** 
	 * @brief Function: void print_str(file_type& file, first_str_type first_str, other_str_type ... str)
	 *
	 * \param file:            file pointer that should be written
	 * \param first_str:       first string to be selected (top of the queue)
	 * \param str:             Next part fo the string
	 *
	 * Log information to a logfile
	 * If log file is not opened, it will open for write
	 */
	template <typename file_type, typename first_str_type, typename... other_str_type>
	void print_str(file_type& file, first_str_type first_str, other_str_type ... str);

	/** 
	 * @brief Function: void print_str(file_type& file, str_type str)
	 *
	 * \param file:            file pointer that should be written
	 * \param str:             Next part fo the string
	 *
	 * Log information to a logfile
	 * If log file is not opened, it will open for write
	 */
	template <typename file_type, typename str_type>
	void print_str(file_type& file, str_type str);

	namespace {
		/**
		 * @brief Global variable logfile
		 *
		 */
		static iofile::File logfile(STRINGIFY(LOGFILE), iofile::mode_e::WO);

	}

}
/** @} */ // End of LogGroup group

template <typename file_type, typename str_type>
void logging::print_str(file_type& file, str_type str) {
	file << str;
	// Flush content to file
	file.flush();
}

template <typename file_type, typename first_str_type, typename... other_str_type>
void logging::print_str(file_type& file, first_str_type first_str, other_str_type ... str) {
	file << first_str;
	logging::print_str(file, str...);
}

template <typename... err_type>
void logging::log_error(err_type... err) {
//	logging::err_mtx.lock();
	std::ostringstream err_oss;
	logging::print_str(err_oss, err...);
	std::string err_str (err_oss.str());
	custom_exception::CustomException snake_error(err_str);
	throw snake_error;
//	logging::err_mtx.unlock();

	exit(1);
}

template <typename... info_type>
void logging::log_info (logging::verb_level_e verbosity, info_type... info) {
	// Locking mutex to avoid other accesses to the logfile for write
	if (verbosity <= static_cast<logging::verb_level_e>(VERBOSITY)) {
//		logging::logfile.file_mtx.lock();
		logging::logfile.write_ofile(info...);
//		logging::logfile.file_mtx.unlock();
	}
}

#endif // LOG_H
