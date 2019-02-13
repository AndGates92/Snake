#ifndef LOG_H
#define LOG_H
/**
 * @copyright
 * @file log.h
 * @author Andrea Gianarda
 * @date 04th of February 2019
 * @brief Log handling header file
*/

#include <iostream>

#include "file.h"
#include "utility.h"

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
	 * Print an message message to the log file if the chosen verbosity is less or equal to the default verbosity
	 */
	#define LOG_INFO(VERBOSITY, ...)\
		log::log_info(VERBOSITY, "File ", __FILE__, " at line ", __LINE__, ": ");\
		log::log_info(VERBOSITY, __VA_ARGS__);\
		log::log_info(VERBOSITY, "\n");

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
			log::log_error("ASSERTION FAILED (", STRINGIFY(EXPR), ")");\
		}
	#else
	#define ASSERT(EXPR)\
		if (!(EXPR)) {\
			LOG_INFO(log::verb_level_e::ZERO,"ASSERTION FAILED (", STRINGIFY(EXPR), ")");\
		}
	#endif // ENABLE_ASSERTIONS



namespace log {

	using iofile::mode_e;
	using iofile::File;

	/** @defgroup LogGroup Log Doxygen Group
	 *  Functions and defines logging progress
	 *  @{
	 */
	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class verb_level_list {
		ZERO,
		LOW,
		MEDIUM,
		HIGH,
		DEBUG
	} verb_level_e;

	/** 
	 * @brief Function: inline void log_error (err_type... err)
	 *
	 * \param err:        string to print using std::cerr
	 *
	 * Log errors to a error stream
	 */
	template <typename... err_type>
	void log_error (err_type... err);

	/** 
	 * @brief Function: inline void log_info (verb_lvl_e verbosity, info_type&... info)
	 *
	 * \param verbosity:   specify the minimum verbosity level required to print a message
	 * \param info:        string to print using std::cout
	 *
	 * Log information to a logfile if desired verbosity level is higher than the requested one
	 */
	template <typename... info_type>
	inline void log_info (log::verb_level_e verbosity, info_type... info);

	/** 
	 * @brief Function: void print_info (info_type... info)
	 *
	 * \param info:        string to print using std::cout
	 *
	 * Log information to a logfile
	 * If log file is not opened, it will open for write
	 */
	template <typename file_type, typename first_str_type, typename... other_str_type>
	inline void print_str(file_type& file, first_str_type first_str, other_str_type ... str);

	template <typename file_type, typename str_type>
	inline void print_str(file_type& file, str_type str);

		class logfileobj {
			public:

				// Constructor
				logfileobj(std::string filename = "", iofile::mode_e access_mode = iofile::mode_e::NO_ACCESS): logstream(filename, access_mode) {};
				// Destructor
				~logfileobj();

				template <typename... info_type>
				void add (info_type... info);

				void close ();

			private:
				iofile::File logstream;
		};

	namespace {
		logfileobj logfile(STRINGIFY(LOGFILE), iofile::mode_e::WO);
	}

/** @} */ // End of LogGroup group
}

template <typename file_type, typename str_type>
inline void log::print_str(file_type& file, str_type str) {
	file << str;
}

template <typename file_type, typename first_str_type, typename... other_str_type>
inline void log::print_str(file_type& file, first_str_type first_str, other_str_type ... str) {
	file << first_str;
	log::print_str(file, str...);
}

template <typename... err_type>
void log::log_error(err_type... err) {
	using std::cerr;

	log::logfile.close();
	log::print_str(std::cerr, "File ",  __FILE__ , " at line ",  __LINE__,  ": ERROR ");
	log::print_str(std::cerr, err...);
	log::print_str(std::cerr, "\n");

}

template <typename... info_type>
inline void log::log_info (log::verb_level_e verbosity, info_type... info) {
	if (verbosity <= static_cast<log::verb_level_e>(VERBOSITY)) {
		log::logfile.add(info...);
	}
}

template <typename... info_type>
void log::logfileobj::add (info_type... info) {

	if (log::logfileobj::logstream.ofile_is_open() == false) {
		log::logfileobj::logstream.open_ofile();
		LOG_INFO(log::verb_level_e::ZERO, "Opened sucesfully log file ", STRINGIFY(LOGFILE));
	}

	log::logfileobj::logstream.write_ofile(info...);
}
#endif // LOG_H
