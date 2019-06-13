#ifndef WINDOW_NODE_H
#define WINDOW_NODE_H
/**
 * @copyright
 * @file window_node.h
 * @author Andrea Gianarda
 * @date 12th of February 2019
 * @brief Window Node header file
*/

#include "window_obj.h"
#include "basic_obj_node.h"
#include "colours.h"

namespace window_node {
	/** @defgroup WindowNodeGroup Window Node Doxygen Group
	 *  Window Node functions and classes
	 *  @{
	 */

	class WindowNode : public basic_obj_node::BasicObjNode<WindowNode>, public window_obj::WindowObj {
		public:
			// Constructor
			/**
			 * @brief Function: WindowNode(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK)
			 *
			 * \param window_title: title of the window
			 * \param window_type: type/group the window belongs to
			 * \param window_width: width of the window
			 * \param window_height: height of the window
			 * \param window_x_pos: position on the x coordinate of the window on the screen
			 * \param window_y_pos: position on the y coordinate of the window on the screen
			 * \param background_colour: background colour of the window
			 *
			 * WindowNode constructor
			 */
			WindowNode(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, colours::palette_e background_colour=colours::palette_e::BLACK): basic_obj_node::BasicObjNode<WindowNode>(), window_obj::WindowObj(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour) {
				std::string pretext ("Window Node Constructor");
				window_node::WindowNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			/**
			 * @brief Function: WindowNode(const WindowNode& copy)
			 *
			 * \param copy: WindowNode to copy
			 *
			 * WindowNode copy constructor
			 */
			WindowNode(const WindowNode& copy) : basic_obj_node::BasicObjNode<WindowNode>(copy), window_obj::WindowObj(copy) {
				std::string pretext ("Window Node Constructor");
				window_node::WindowNode::print_info(logging::verb_level_e::LOW, pretext);
			}

			// Destructor
			/**
			 * @brief Function: ~WindowNode()
			 *
			 * Destructor of WindowNode
			 */
			~WindowNode();

			/**
			 * @brief Function: void print_info(logging::verb_level_e verbosity, std::string pretext)
			 *
			 * \param verbosity: verbosity level
			 * \param pretext: text to prepend to the WindowNode information
			 *
			 * Print WindowNode information
			 */
			void print_info(logging::verb_level_e verbosity, std::string pretext);

			/**
			 * @brief Function: void destroy_name()
			 *
			 * Delete a node
			 */
			void destroy_node();

		protected:

		private:
	};
	/** @} */ // End of WindowNodeGroup group
}

#endif // WINDOW_NODE_H
