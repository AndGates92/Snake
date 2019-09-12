/**
 * @copyright
 * @file graphics_utils.cpp
 * @author Andrea Gianarda
 * @date 27th February 2019
 * @brief Graphics utility functions
 */

#include <string>
#include <iostream>
#include <fstream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "colours.h"
#include "logging.h"
#include "window_list.h"
#include "window_obj.h"
#include "graphics_utils.h"

/** @addtogroup GraphicsUtilsGroup
 *
 *  @{
 */
namespace graphics_utils {
	namespace {
		/**
		 * @brief pointer to windows
		 *
		 */
		static window_list::WindowList windows;
	}
}
/** @} */ // End of addtogroup GraphicsUtilsGroup

void graphics_utils::init_window_list() {
	windows = window_list::WindowList("Window");
}

// Delete window having the ID passed as input
void graphics_utils::delete_win_id(int win_id) {
	LOG_INFO(logging::verb_level_e::HIGH,"[Delete window ID] Delete window with ID: ", win_id);
	windows.delete_by_win_id(win_id);
}

// Search window having the ID passed as input
window_obj::WindowObj graphics_utils::search_win_id(int win_id) {
	LOG_INFO(logging::verb_level_e::HIGH,"[Search window] Search window with ID: ", win_id);
	return windows.search_by_win_id(win_id);
}

void graphics_utils::delete_window() {
	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::HIGH,"[Delete window] Delete window with ID: ", win_id);

	graphics_utils::delete_win_id(win_id);
}

void graphics_utils::delete_all_windows() {
	LOG_INFO(logging::verb_level_e::LOW, "[Delete all window] Delete all windows");
	LOG_INFO(logging::verb_level_e::LOW, windows);
	windows.delete_all_elements();
//	delete windows;
}

window_list::WindowList & graphics_utils::get_window_ptr() {
	return windows;
}

// Create new window
int graphics_utils::win_node_add(std::string window_title, std::string window_type, int window_width, int window_height, int window_x_pos, int window_y_pos, colours::palette_e background_colour) {
	int win_id = windows.add_element(window_title, window_type, window_width, window_height, window_x_pos, window_y_pos, background_colour);
	return win_id;
}

void graphics_utils::refresh_window(int value) {

	std::vector<window_obj::WindowObj> & win_vector(graphics_utils::windows.get_vector());

	// Refresh windows
	for (auto win_node : win_vector) {

		int curr_win_id = win_node.get_win_id();

		LOG_INFO(logging::verb_level_e::DEBUG,"[Refresh window] Window ID: current ", curr_win_id);

		glutSetWindow(curr_win_id);
		glutPostRedisplay();

	}

	// Restart timer
	glutTimerFunc(value, graphics_utils::refresh_window, value);

}


void graphics_utils::save_window(iofile::File & savefile) {

	int win_node_cnt = 0;

	std::vector<window_obj::WindowObj> & win_vector(graphics_utils::windows.get_vector());

	for (auto win_node : win_vector) {
		savefile.write_ofile("//******************************\n");
		savefile.write_ofile("// Window ", win_node_cnt, "\n");
		savefile.write_ofile("//******************************\n");
		win_node.save_data(savefile);

		savefile.write_ofile("\n");

		// Save temporary obstacle
		win_node_cnt++;
	}

}
