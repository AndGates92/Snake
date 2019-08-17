/**
 * @copyright
 * @file game_graphics.cpp
 * @author Andrea Gianarda
 * @date 27th February 2019
 * @brief Game graphics functions
 */

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "settings.h"
#include "logging.h"
#include "colours.h"
#include "menu.h"
#include "graphics_utils.h"
#include "graphics.h"
#include "game_graphics.h"
#include "game_utils.h"
#include "snake_list.h"
#include "snake_unit.h"
#include "snake_utils.h"

using namespace std;
using namespace logging;
using namespace menu;
using namespace graphics;
using namespace game_graphics;
using namespace graphics_utils;
using namespace snake_utils;

void game_graphics::display_game_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Display Game Callback] Display Game Callback for window ID: ", win_id);

	double win_width = 0.0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	int win_width_int = (int) win_width;

	double win_height = 0.0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);
	int win_height_int = (int) win_height;

	glPixelStoref(GL_PACK_ALIGNMENT, 1);
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

	// Store pixels in pixels array
	unsigned char * pixels = game_utils::get_game_pixel_array<unsigned char>(win_width_int, win_height_int);

	glDrawPixels(win_width_int, win_height_int, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	delete [] pixels;

	// swap buffers to display the frame
	glutSwapBuffers();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::keyboard_game_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'f':
			// Explicitely limit scope of variable speed and speed_incr
			{
				int speed = snake_settings.get_speed();
				int speed_incr = snake_settings.get_speed_incr();
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Speed up snake to ", speed, " because of pressing key ", key);
				snake_settings.set_speed(speed + speed_incr);
			}
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case 's':
			// Explicitely limit scope of variable speed and speed_incr
			{
				int speed = snake_settings.get_speed();
				int speed_incr = snake_settings.get_speed_incr();

				if (speed > speed_incr) {
					snake_settings.set_speed(speed - speed_incr);
				}
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Slow down snake to ", speed, " because of pressing key ", key);
				ASSERT(snake_settings.get_speed() > 0)
				// force glut to call the display function
			}
			glutPostRedisplay();
			break;
		case 'm':
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Save game because of pressing key ", key);
			// Explicitely limit scope of variable savefilename
			{
				std::string savefilename (snake_settings.get_save_filename());
				game_utils::save_game(savefilename);
			}
			break;
		case 'p':
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Start/Pause game because of pressing key ", key);
			// Explicitely limit scope of variable game_status
			{
				settings::game_status_e game_status = snake_settings.get_game_status();

				if (game_status == settings::game_status_e::RUNNING) {
					snake_settings.set_game_status(settings::game_status_e::PAUSED);
				} else if (game_status == settings::game_status_e::PAUSED) {
					snake_settings.set_game_status(settings::game_status_e::RUNNING);
				}
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Game state: ", snake_settings.get_game_status());
			}
			break;
		case 'r':
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Restart game because of pressing key ", key);
			snake_settings.set_game_status(settings::game_status_e::RESTART);
			break;
		case 'q':
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Exit program because of pressing key ", key);
			snake_settings.set_game_status(settings::game_status_e::EXIT);
			break;
		default:
			break;
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::specialkey_game_cb(int key, int x, int y) {

	snake_list::SnakeList * snake_ptr (game_utils::get_snake_ptr());
	snake_unit::SnakeNode * snake_head (snake_ptr->get_head());
	snake_utils::direction_e snake_head_dir = snake_head->get_direction();

	bool auto_ride = snake_settings.get_auto_ride_flag();

	if (auto_ride == false) {
		switch (key) {
			case GLUT_KEY_UP:
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to UP because of pressing key Arrow Up");
				if ((snake_head_dir == snake_utils::direction_e::RIGHT) || (snake_head_dir == snake_utils::direction_e::LEFT)) {
					game_utils::set_head_dir(snake_utils::direction_e::UP);
				}
				break;
			case GLUT_KEY_DOWN:
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to DOWN because of pressing key Arrow Down");
				if ((snake_head_dir == snake_utils::direction_e::RIGHT) || (snake_head_dir == snake_utils::direction_e::LEFT)) {
					game_utils::set_head_dir(snake_utils::direction_e::DOWN);
				}
				break;
			case GLUT_KEY_LEFT:
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to LEFT because of pressing key Arrow Left");
				if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
					game_utils::set_head_dir(snake_utils::direction_e::LEFT);
				}
				break;
			case GLUT_KEY_RIGHT:
				LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to RIGHT because of pressing key Arrow Right");
				if ((snake_head_dir == snake_utils::direction_e::UP) || (snake_head_dir == snake_utils::direction_e::DOWN)) {
					game_utils::set_head_dir(snake_utils::direction_e::RIGHT);
				}
				break;
			default:
				break;
		}
	} else {
		LOG_INFO(logging::verb_level_e::ZERO,"[Keyboard Game Callback] Cannot change direction because automatic ride is set to ", auto_ride);
	}
	// force glut to call the display function
	glutPostRedisplay();
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void game_graphics::mouse_game_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void game_graphics::idle_game_cb() {

	int win_id = glutGetWindow();

	int win_width = glutGet(GLUT_WINDOW_WIDTH);
	int win_height = glutGet(GLUT_WINDOW_HEIGHT);

	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	colours::palette_e colour = snake_settings.get_snake_colour();

	snake_list::SnakeList * snake_ptr (game_utils::get_snake_ptr());

	LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Game Callback] Idle Game Callback for window ID: ", win_id);

	settings::game_status_e game_status = snake_settings.get_game_status();

	if (game_status == settings::game_status_e::RUNNING) {

		bool obs_eaten = game_utils::contact_between_snake_obs();
		// Store speed locally because it can be changed anytime by the user. The update will be accounted for next time round
		int snake_speed = snake_settings.get_speed();
		if (obs_eaten == true) {

			game_utils::add_obstacle();

			snake_unit::SnakeNode * snake_head = snake_ptr->get_head();
			int new_snake_node_x = snake_head->get_x_centre();
			int new_snake_node_y = snake_head->get_y_centre();
			snake_utils::direction_e snake_head_dir = snake_head->get_direction();

			if (snake_head_dir == snake_utils::direction_e::RIGHT) {
				new_snake_node_x = (snake_head->get_x_centre() + node_width) % win_width;
				new_snake_node_y = snake_head->get_y_centre();
			} else if (snake_head_dir == snake_utils::direction_e::LEFT) {
				new_snake_node_x = (snake_head->get_x_centre() - node_width);
				// If head is vry close to boarded, unit in front of it might be outside of window (negative X)
				if (new_snake_node_x < 0) {
					new_snake_node_x += win_width;
				}
				new_snake_node_y = snake_head->get_y_centre();
			} else if (snake_head_dir == snake_utils::direction_e::UP) {
				new_snake_node_y = (snake_head->get_y_centre() + node_height) % win_height;
				new_snake_node_x = snake_head->get_x_centre();
			} else if (snake_head_dir == snake_utils::direction_e::DOWN) {
				new_snake_node_y = (snake_head->get_y_centre() - node_height);
				// If head is vry close to boarded, unit in front of it might be outside of window (negative X)
				if (new_snake_node_y < 0) {
					new_snake_node_y += win_height;
				}
				new_snake_node_x = snake_head->get_x_centre();
			}

			game_utils::add_snake_node(new_snake_node_x, new_snake_node_y, node_width, node_height, snake_head_dir, colour);

			int snake_units = snake_settings.get_snake_units();
			snake_settings.set_snake_units(snake_units + 1);

			int score = snake_settings.get_score();
			snake_settings.set_score(score + snake_speed);

		} else {

			bool auto_ride = snake_settings.get_auto_ride_flag();
			if (auto_ride == true) {
				game_utils::auto_change_dir();
			}

			snake_ptr->move(snake_speed, win_width, win_height, game_utils::get_head_dir());

		}

		snake_ptr->check_collision(win_width, win_height);
	} else if (game_status == settings::game_status_e::RESTART) {
		game_utils::free_game_memory();
		graphics::declare_game();

		// Initialize game
		game_utils::init_game();

		// Initialize game parameters
		game_utils::init_game_parameters();

	} else if (game_status == settings::game_status_e::EXIT) {
		// Explicitely limit scope of variable savefilename
		{
			std::string dumpfilename (snake_settings.get_dump_filename());
			game_utils::save_game(dumpfilename);
		}
		graphics_utils::delete_window();
		game_utils::free_game_memory();
		exit(EXIT_SUCCESS);
	} else {
		ASSERT(game_status == settings::game_status_e::PAUSED);
	}

//	int win_id_new = glutGetWindow();
//	if (win_id_new != 0) {
//		LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Game Callback] Idle Game Callback before glutPostRedisplay for window ID: ", win_id_new);
		// force glut to call the display function
		glutPostRedisplay();
//	}

}

void game_graphics::wrapper_game_cb() {
	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Game Graphics Wrapper] Enter game graphics wrapper for window ID ", win_id);
	glutDisplayFunc( display_game_cb );
	glutKeyboardFunc( keyboard_game_cb );
	glutReshapeFunc( graphics::reshape_cb );
	glutIdleFunc( graphics::idle_cb );
	glutSpecialFunc( specialkey_game_cb );
	glutMouseFunc( mouse_game_cb );
}
