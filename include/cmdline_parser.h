#ifndef CMDLINE_PARSER_H
#define CMDLINE_PARSER_H
/**
 * @copyright
 * @file cmdline_parser.h
 * @author Andrea Gianarda
 * @date 20th May 2019
 * @brief Command Line Parser header file
*/

/** @defgroup CmdlineParserGroup Command Line Parser Doxygen Group
 *  Command Line Parser functions and classes
 *  @{
 */
namespace cmdline_parser {

	/**
	 * @brief Object type
	 *
	 */
	typedef enum class obj_list {
		SNAKE,    /**< Snake */
		OBSTACLE, /**< Obstacle */
		WINDOW,   /**< Window */
		MENU,     /**< Menu */
		SETTINGS, /**< Settings */
		TILE,     /**< Tile */
		UNKNOWN   /**< Unknown */
	} obj_e;

	/**
	 * @brief Function: bool parse(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * Parse command line
	 */
	bool parse(int argc, char** argv);

	/**
	 * @brief Function: void process()
	 *
	 * Process command lines:
	 * - read input file (if provided)
	 * - create objects
	 */
	void process();

	/**
	 * @brief Function: void extract_inputfile_info()
	 *
	 * Extract informations from the input file
	 */
	void extract_inputfile_info();

	/**
	 * @brief Function: void reset_common_var(cmdline_parser::obj_e & object, obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction)
	 *
	 * \param object: type of object to create (See values supported by enumerated type obj_e)
	 * \param type: string matching the object type
	 * \param title: label of the object
	 * \param x_centre: x coordinate of the object
	 * \param y_centre: y coordinate of the object
	 * \param width: width of the object
	 * \param height: height of the object
	 * \param colour: colour of the object
	 * \param direction: direction of movement
	 *
	 * Assign default value to variables required to create an object as information are extracted from the input file
	 */
	void reset_common_var(cmdline_parser::obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction);

	/**
	 * @brief Function: void assign_common_var(std::string var_name, std::string var_value, obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction)
	 *
	 * \param var_name: variable name extracted from the line
	 * \param var_value: variable value extracted from the line
	 * \param object: type of object to create (See values supported by enumerated type obj_e)
	 * \param type: string matching the object type
	 * \param title: label of the object
	 * \param x_centre: x coordinate of the object
	 * \param y_centre: y coordinate of the object
	 * \param width: width of the object
	 * \param height: height of the object
	 * \param colour: colour of the object
	 * \param direction: direction of movement
	 *
	 * Assign variables to create an object as information are extracted from the input file
	 */
	void assign_common_var(std::string var_name, std::string var_value, obj_e & object, std::string & type, std::string & title, int & x_centre, int & y_centre, int & width, int & height, colours::palette_e & colour, snake_utils::direction_e & direction);

	/**
	 * @brief Function: void decode_line(std::string line, std::string & var_name, std::string & var_value)
	 *
	 * \param line: line to parse
	 * \param var_name: variable name extracted from the line
	 * \param var_value: variable value extracted from the line
	 *
	 * Decode line word by word (It is expected the format <varName>: <varValue>)
	 */
	void decode_line(std::string line, std::string & var_name, std::string & var_value);

	/**
	 * @brief Function: bool extract_word(std::string line, std::string::size_type start_pos, std::string & word, std::string::size_type & end_pos)
	 *
	 * \param line: line to parse
	 * \param start_pos: starting position for the search
	 * \param end_pos: ending position for the search
	 * \param word: word found
	 *
	 * \return boolean value of the validy of output word
	 *
	 * Decode a word from the input line
	 */
	bool extract_word(std::string line, std::string::size_type start_pos, std::string & word, std::string::size_type & end_pos);

	/**
	 * @brief Function: bool detect_comment_line(std::string line)
	 *
	 * \param line: line to check
	 *
	 * \return boolean value whether it is a comment line (true) or not (false)
	 *
	 * Detect comment lines
	 */
	bool detect_comment_line(std::string line);

	/**
	 * @brief Function: void delete_special_characters(std::string & word)
	 *
	 * \param word: string to check for alpha-numeric characters
	 *
	 * Delete non-alpha numeric characters. Keep only A-Z, a-z and 0-9
	 */
	void delete_special_characters(std::string & word);

	/**
	 * @brief Function: cmdline_parser::obj_e str_to_obj (std::string type)
	 *
	 * \param type: string matching the object type
	 *
	 * \return object type as enumerate list obj_e
	 *
	 * Convert string into object type obj_e
	 */
	cmdline_parser::obj_e str_to_obj (std::string type);

	// Overload << operator for obj_e
	/**
	 * @brief Function: std::ostream& operator<< (std::ostream& os, cmdline_parser::obj_e obj)
	 *
	 * \param obj: type of object to create (See values supported by enumerated type obj_e)
	 * \param os: output stream
	 *
	 * \return text to pass to the calling output stream
	 *
	 * Overload << operator for type obj_e
	 */
	std::ostream& operator<< (std::ostream& os, cmdline_parser::obj_e obj);

	/**
	 * @brief Function: void create_obj (cmdline_parser::obj_e object, std::string type, std::string title, int x_centre, int y_centre, int width, int height, colours::palette_e colour, snake_utils::direction_e direction)
	 *
	 * \param object: type of object to create (See values supported by enumerated type obj_e)
	 * \param type: string matching the object type
	 * \param title: label of the object
	 * \param x_centre: x coordinate of the object
	 * \param y_centre: y coordinate of the object
	 * \param width: width of the object
	 * \param height: height of the object
	 * \param colour: colour of the object
	 * \param direction: direction of movement
	 *
	 * Create object
	 */
	void create_obj (cmdline_parser::obj_e object, std::string type, std::string title, int x_centre, int y_centre, int width, int height, colours::palette_e colour, snake_utils::direction_e direction);
}
/** @} */ // End of CmdlineParserGroup group


#endif // CMDLINE_PARSER_H
