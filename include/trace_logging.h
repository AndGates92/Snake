#ifndef TRACE_LOGGING_H
#define TRACE_LOGGING_H
/**
 * @copyright
 * @file trace_logging.h
 * @author Andrea Gianarda
 * @date 15th September 2019
 * @brief Trace Logging header file
*/

/** @defgroup TraceLogging Trace Logging Doxygen Group
 *  Trace Logging functions and classes
 *  @{
 */
namespace trace_logging {

	namespace {
		/**
		 * @brief Number of entries to fetch from the backtrace
		 *
		 */
		const static int backtrace_entries = 15;
	}

	/** 
	 * @brief Function: void print_backtrace(int file_descriptor)
	 *
	 * \param file_descriptor:            file pointer that should be written
	 *
	 * Log backtrace to a logfile
	 */
	void print_backtrace(int file_descriptor);
}
/** @} */ // End of TraceLoggingGroup group


#endif // TRACE_LOGGING_H
