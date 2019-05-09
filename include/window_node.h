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
			WindowNode(std::string window_title = "", std::string window_type = "Window", int window_width = 0, int window_height = 0, int window_x_pos = WIN_POS_X, int window_y_pos = WIN_POS_Y, void (*EntryFunc)(int) = nullptr, void (*ItemsFunc)() = nullptr, void (*WrapperFunc)()=nullptr, colours::palette_e background_colour=colours::palette_e::BLACK): basic_obj_node::BasicObjNode<WindowNode>(), window_obj::WindowObj(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, EntryFunc, ItemsFunc, WrapperFunc, background_colour) {
				std::string pretext ("Window Node Constructor");
				window_node::WindowNode::print_info(logging::verb_level_e::LOW, pretext);
			};

			WindowNode(const WindowNode& copy) : basic_obj_node::BasicObjNode<WindowNode>(copy), window_obj::WindowObj(copy) {
				std::string pretext ("Window Node Constructor");
				window_node::WindowNode::print_info(logging::verb_level_e::LOW, pretext);
			}

			// Destructor
			~WindowNode();

			void print_info(logging::verb_level_e verbosity, std::string pretext);
			void destroy_node();

		protected:

		private:
	};
	/** @} */ // End of WindowNodeGroup group
}

#endif // WINDOW_NODE_H
