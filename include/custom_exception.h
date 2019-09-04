#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H
/**
 * @copyright
 * @file custom_exception.h
 * @author Andrea Gianarda
 * @date 04th September 2019
 * @brief Custom Exception header file
*/

#include <string>
#include <exception>

#include "logging.h"

/** @defgroup CustomExceptionGroup Custom Exception Doxygen Group
 *  Custom Exception functions and classes
 *  @{
 */
namespace custom_exception {

	/**
	 * @brief CustomException class
	 *
	 */
	class CustomException : public std::exception {
		public :
			// Constructor
			/**
			 * @brief Function: explicit CustomException(const std::string exception_message)
			 *
			 * \param exception_message: exception message
			 *
			 * CustomException constructor
			 */
			explicit CustomException(const std::string exception_message) : message (exception_message) {
				LOG_INFO(logging::verb_level_e::LOW, "Constructor")
			};

			// Destructor
			/**
			 * @brief Function: virtual ~CustomException() throw()
			 *
			 * Destructor of CustomException
			 */
			virtual ~CustomException() throw();

			/**
			 * @brief Function: virtual const char * what() const throw()
			 *
			 * what() function overload
			 */
			virtual const char * what() const throw();

		protected :

		private :

			std::string message;

	};

}
/** @} */ // End of CustomExceptionGroup group

#endif // CUSTOM_EXCEPTION_H
