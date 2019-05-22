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

	/**
	 * @brief Object type
	 *
	 */
	typedef enum class obj_list {
		SNAKE,    /**< Snake */
		OBSTACLE, /**< Obstacle */
		WINDOW,   /**< Window */
		MENU,     /**< Menu */
		SETTING,  /**< Setting */
		TILE,     /**< Tile */
		UNKNOWN   /**< Unknown */
	} obj_e;


	void parse(int argc, char** argv);

	void process();

	void extract_inputfile_info();

	void reset_common_var(cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction);

	//void decode_line(std::string line, obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction);
	void decode_line(std::string line);

	int extract_word(std::string line, std::string::size_type start_pos, std::string & word, std::string::size_type & end_pos);

	bool check_line(std::string line);

	// Overload << operator for obj_e
	std::ostream& operator<< (std::ostream& os, cmdline_parser::obj_e obj);
	/** @} */ // End of CmdlineParserGroup group
}


#endif // CMDLINE_PARSER_H
