#ifndef CMDLINE_PARSER_H
#define CMDLINE_PARSER_H
/**
 * @copyright
 * @file cmdline_parser.h
 * @author Andrea Gianarda
 * @date 20th May 2019
 * @brief Command Line Parser header file
*/

namespace cmdline_parser {
	/** @defgroup CmdlineParserGroup Command Line Parser Doxygen Group
	 *  Command Lie Parser functions and classes
	 *  @{
	 */

	void parse(int argc, char** argv);

	void process();

	void extract_inputfile_info();

	/** @} */ // End of CmdlineParserGroup group
}


#endif // CMDLINE_PARSER_H
