#ifndef MAIN_H
#define MAIN_H
/**
 * @copyright
 * @file basic_list.h
 * @author Andrea Gianarda
 * @date 16th September 2019
 * @brief Main header file
*/

/** @defgroup MainGroup Main Log Doxygen Group
 *  Functions and defines logging progress
 *  @{
 */
/**
 * @brief Function: void signal_handler()
 *
 * Signal handler. Prints backtrace
 */
void signal_handler(int sig_id);
/** @} */ // End of MainGroup group

#endif // MAIN_H
