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
#include "window_obj.h"
#include "snake_list.h"
#include "snake_node.h"

using namespace std;
using namespace logging;
using namespace menu;
using namespace graphics;
using namespace game_graphics;
using namespace graphics_utils;
using namespace window_obj;
using namespace snake_list;
using namespace snake_node;

namespace game_graphics {

	namespace {
		/**
		 * @brief Direction of the snake head
		 *
		 */
		snake_node::direction_e head_dir;
	}
}

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
	unsigned char * pixels = game_graphics::get_game_pixel_array<unsigned char>(win_width_int, win_height_int);

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
				game_graphics::save_game(savefilename);
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

	snake_node::SnakeNode * snake_head (game_graphics::snake->get_head());
	snake_node::direction_e snake_head_dir = snake_head->get_direction();

	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to UP because of pressing key Arrow Up");
			if ((snake_head_dir == snake_node::direction_e::RIGHT) | (snake_head_dir == snake_node::direction_e::LEFT)) {
				game_graphics::head_dir = snake_node::direction_e::UP;
			}
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to DOWN because of pressing key Arrow Down");
			if ((snake_head_dir == snake_node::direction_e::RIGHT) | (snake_head_dir == snake_node::direction_e::LEFT)) {
				game_graphics::head_dir = snake_node::direction_e::DOWN;
			}
			break;
		case GLUT_KEY_LEFT:
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to LEFT because of pressing key Arrow Down");
			if ((snake_head_dir == snake_node::direction_e::UP) | (snake_head_dir == snake_node::direction_e::DOWN)) {
				game_graphics::head_dir = snake_node::direction_e::LEFT;
			}
			break;
		case GLUT_KEY_RIGHT:
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Change direction to RIGHT because of pressing key Arrow Down");
			if ((snake_head_dir == snake_node::direction_e::UP) | (snake_head_dir == snake_node::direction_e::DOWN)) {
				game_graphics::head_dir = snake_node::direction_e::RIGHT;
			}
			break;
		default:
			break;
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

	LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Game Callback] Idle Game Callback for window ID: ", win_id);

	settings::game_status_e game_status = snake_settings.get_game_status();

	if (game_status == settings::game_status_e::RUNNING) {
		bool obs_eaten = contact_between_snake_obs();
		// Store speed locally because it can be changed anytime by the user. The update will be accounted for next time round
		int snake_speed = snake_settings.get_speed();
		if (obs_eaten == true) {

			game_graphics::add_obstacle();

			snake_node::SnakeNode * snake_head = game_graphics::snake->get_head();
			int new_snake_node_x = snake_head->get_x_centre();
			int new_snake_node_y = snake_head->get_y_centre();
			snake_node::direction_e snake_head_dir = snake_head->get_direction();

			if (snake_head_dir == snake_node::direction_e::RIGHT) {
				new_snake_node_x = (snake_head->get_x_centre() + node_width) % win_width;
				new_snake_node_y = snake_head->get_y_centre();
			} else if (snake_head_dir == snake_node::direction_e::LEFT) {
				new_snake_node_x = (snake_head->get_x_centre() - node_width);
				// If head is vry close to boarded, unit in front of it might be outside of window (negative X)
				if (new_snake_node_x < 0) {
					new_snake_node_x += win_width;
				}
				new_snake_node_y = snake_head->get_y_centre();
			} else if (snake_head_dir == snake_node::direction_e::UP) {
				new_snake_node_y = (snake_head->get_y_centre() + node_height) % win_height;
				new_snake_node_x = snake_head->get_x_centre();
			} else if (snake_head_dir == snake_node::direction_e::DOWN) {
				new_snake_node_y = (snake_head->get_y_centre() - node_height);
				// If head is vry close to boarded, unit in front of it might be outside of window (negative X)
				if (new_snake_node_y < 0) {
					new_snake_node_y += win_height;
				}
				new_snake_node_x = snake_head->get_x_centre();
			}

			game_graphics::snake->add_node(new_snake_node_x, new_snake_node_y, node_width, node_height, snake_head_dir, colour);

			int snake_units = snake_settings.get_snake_units();
			snake_settings.set_snake_units(snake_units + 1);

			int score = snake_settings.get_score();
			snake_settings.set_score(score + snake_speed);

		} else {

			game_graphics::snake->move(snake_speed, win_width, win_height, game_graphics::head_dir);

		}

		game_graphics::snake->check_collision(win_width, win_height);
	} else if (game_status == settings::game_status_e::RESTART) {
		game_graphics::free_game_memory();
		graphics::start_game();
	} else if (game_status == settings::game_status_e::EXIT) {
		// Explicitely limit scope of variable savefilename
		{
			std::string dumpfilename (snake_settings.get_dump_filename());
			game_graphics::save_game(dumpfilename);
		}
		game_graphics::free_game_memory();
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


void game_graphics::init_snake_list() {
	std::string type("Snake");
	game_graphics::snake = new snake_list::SnakeList(type);
	if (game_graphics::snake == nullptr) {
		LOG_ERROR("Can't allocate memory for snake list ", type, ".");
	}
}

void game_graphics::init_obstacle_list() {
	std::string type("Obstacle");
	game_graphics::obstacles = new obstacle_list::ObstacleList(type);
	if (game_graphics::obstacles == nullptr) {
		LOG_ERROR("Can't allocate memory for obstacle list ", type, ".");
	}
}

snake_list::SnakeList * & game_graphics::get_snake_ptr() {
	return game_graphics::snake;
}

void game_graphics::populate_snake_list() {
	int centre_x = snake_settings.get_head_centre_x();
	int centre_y = snake_settings.get_head_centre_y();

	int snake_units = snake_settings.get_snake_units();
	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	snake_node::direction_e head_dir = snake_settings.get_head_dir();
	colours::palette_e colour = snake_settings.get_snake_colour();

	for (int unit_no=0; unit_no < snake_units; unit_no++) {

		game_graphics::snake->add_node(centre_x, centre_y, node_width, node_height, head_dir, colour);
		//game_graphics::snake->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, game_graphics::init_head_dir, (colours::palette_e) unit_no);
		centre_x += node_width;
		//game_graphics::snake->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, game_graphics::init_head_dir, colours::palette_e::RED);
		//centre_y += game_graphics::node_height;

	}

	// Colour snake_head differently to ease debug
	snake_node::SnakeNode * snake_head = game_graphics::snake->get_head();
	snake_head->set_colour(colours::palette_e::YELLOW);

}

void game_graphics::populate_obstacle_list() {

	int obs_no = snake_settings.get_obs_no();

	for (int obs=0; obs < obs_no; obs++) {
		game_graphics::add_obstacle();
	}

}

void game_graphics::init_game_parameters() {
	game_graphics::head_dir = snake_settings.get_head_dir();
}

void game_graphics::init_game() {

	game_graphics::init_snake_list();
	game_graphics::init_obstacle_list();
	game_graphics::init_game_parameters();

	game_graphics::populate_snake_list();
	game_graphics::populate_obstacle_list();
}

bool game_graphics::contact_between_snake_obs() {

	// Retrieve snake head informations
	snake_node::SnakeNode * snake_head = game_graphics::snake->get_head();
	int snake_head_x = snake_head->get_x_centre();
	int snake_head_width = snake_head->get_width();
	int snake_head_x_min = snake_head_x - snake_head_width/2;
	int snake_head_x_max = snake_head_x + snake_head_width/2;
	int snake_head_y = snake_head->get_y_centre();
	int snake_head_height = snake_head->get_height();
	int snake_head_y_min = snake_head_y - snake_head_height/2;
	int snake_head_y_max = snake_head_y + snake_head_height/2;

//cout << "Snake boundaries X " << snake_head_x_min << " - " << snake_head_x_max << " Y " << snake_head_y_min << " - " << snake_head_y_max << endl;

	// obstacle pointer
	obstacle::ObstacleNode * curr_node = game_graphics::obstacles->get_head();

	bool contact = false;

	while (curr_node != nullptr) {
		int obs_x = curr_node->get_x_centre();
		int obs_width = curr_node->get_width();
		int obs_x_min = obs_x - obs_width/2;
		int obs_x_max = obs_x + obs_width/2;
		int obs_y = curr_node->get_y_centre();
		int obs_height = curr_node->get_height();
		int obs_y_min = obs_y - obs_height/2;
		int obs_y_max = obs_y + obs_height/2;

//cout << "Obs boundaries X " << obs_x_min << " - " << obs_x_max << " Y " << obs_y_min << " - " << obs_y_max << endl;

		// Save temporary obstacle
		obstacle::ObstacleNode * node_tmp = curr_node;
		curr_node = curr_node->get_next();

		if (
			(
			// snake head X minimum coordinate is between obstacle X minimum and X maximum
			((snake_head_x_min <= obs_x_max) & (snake_head_x_min >= obs_x_min)) |
			// snake head X maximum coordinate is between obstacle X minimum and X maximum
			((snake_head_x_max <= obs_x_max) & (snake_head_x_max >= obs_x_min))
			) & (
			// snake head Y minimum coordinate is between obstacle Y minimum and X maximum
			((snake_head_y_min <= obs_y_max) & (snake_head_y_min >= obs_y_min)) |
			// snake head Y maximum coordinate is between obstacle Y minimum and X maximum
			((snake_head_y_max <= obs_y_max) & (snake_head_y_max >= obs_y_min))
			)
		) {

			LOG_INFO(logging::verb_level_e::MEDIUM,"[Contact snake-obstacle] Contact between snake head at (", snake_head_x, ", ", snake_head_y, ") and obstacle at (", obs_x, ", ", obs_y, ")");
			// Delete obstacle after contact
			game_graphics::obstacles->remove_node(node_tmp);
			contact = true;
		}
	}

	return contact;
}

void game_graphics::add_obstacle() {

	double win_width = 0.0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	int win_width_int = (int) win_width;

	double win_height = 0.0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);
	int win_height_int = (int) win_height;

	int node_height = snake_settings.get_node_height();
	int node_width = snake_settings.get_node_width();
	colours::palette_e colour = snake_settings.get_obs_colour();

	// Random coordinates must be within node_width/2 and (win_width-node_width/2)
	int centre_x = (rand() % (win_width_int - node_width)) + node_width/2;

	// Random coordinates must be within node_height/2 and (win_height-node_height/2)
	int centre_y = (rand() % (win_height_int - node_height)) + node_height/2;

	//game_graphics::obstacles->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, colours::palette_e::PURPLE);
	game_graphics::obstacles->add_node(centre_x, centre_y, node_width, node_height, colour);
}

void game_graphics::free_obstacle_list() {
	game_graphics::obstacles->~ObstacleList();
	delete game_graphics::obstacles;
}

void game_graphics::free_snake_list() {
	game_graphics::snake->~SnakeList();
	delete game_graphics::snake;
}

void game_graphics::free_window_list() {
	graphics_utils::delete_all_windows();
}

void game_graphics::save_game(std::string filename) {
	// obstacle pointer
	snake_node::SnakeNode * curr_snake_node = game_graphics::snake->get_head();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Save Game] Saving game to file: ", filename);

	iofile::File save(filename, iofile::mode_e::WO);

	int snake_node_cnt = 0;

	save.write_ofile("Dump: ", snake_settings.get_dump_filename(), "\n");
	save.write_ofile("Save: ", snake_settings.get_save_filename(), "\n");
	save.write_ofile("\n");

	save.write_ofile("//******************************\n");
	save.write_ofile("// Stat Windows\n");
	save.write_ofile("//******************************\n");
	save.write_ofile("Type: Tile\n");
	save.write_ofile("Width: ", snake_settings.get_tile_width(), "\n");
	save.write_ofile("Height: ", snake_settings.get_tile_height(), "\n");
	save.write_ofile("Score: ", snake_settings.get_score(), "\n");
	save.write_ofile("\n");

	save.write_ofile("Speed: ", snake_settings.get_speed(), "\n");
	save.write_ofile("Snake Units: ", snake_settings.get_snake_units(), "\n");
	save.write_ofile("\n");

	while (curr_snake_node != nullptr) {
		save.write_ofile("//******************************\n");
		save.write_ofile("// Snake Node ", snake_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		curr_snake_node->save_data(save);

		save.write_ofile("\n");

		// Save temporary obstacle
		curr_snake_node = curr_snake_node->get_next();
		snake_node_cnt++;
	}

	// obstacle pointer
	obstacle::ObstacleNode * curr_obs_node = game_graphics::obstacles->get_head();

	save.write_ofile("Obstacles: ", snake_settings.get_obs_no(), "\n");
	save.write_ofile("\n");

	int obs_node_cnt = 0;

	while (curr_obs_node != nullptr) {

		save.write_ofile("//******************************\n");
		save.write_ofile("// Obstacle Node ", obs_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		curr_obs_node->save_data(save);

		// Save temporary obstacle
		curr_obs_node = curr_obs_node->get_next();
		obs_node_cnt++;
	}

}

void game_graphics::free_game_memory() {
	graphics_utils::delete_window();
	game_graphics::free_obstacle_list();
	game_graphics::free_snake_list();
	snake_settings.~Settings();
}
