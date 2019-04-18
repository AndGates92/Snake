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
#include "menu.h"
#include "graphics_utils.h"
#include "game_graphics.h"
#include "window_obj.h"
#include "snake_list.h"
#include "snake_node.h"

using namespace std;
using namespace logging;
using namespace menu;
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

void game_graphics::reshape_game_cb(int width, int height) {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Reshape Game Callback] Reshape Game Callback window width to ", width, " and window height to ", height);

	int win_id = 0;
	win_id = glutGetWindow();

	window_node::WindowNode * node (graphics_utils::search_win_id(win_id));
	window_obj::WindowObj window (node->get_obj());

	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( game_graphics::zoom, (GLdouble)width/(GLdouble)height, game_graphics::zNear, game_graphics::zFar );

//	glClear(GL_COLOR_BUFFER_BIT);

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
		case 'q':
			graphics_utils::delete_window();
			game_graphics::free_obstacle_list();
			game_graphics::free_snake_list();
			LOG_INFO(logging::verb_level_e::DEBUG,"[Keyboard Game Callback] Exit program because of pressing key ", key);
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
	graphics_utils::palette_e color = snake_settings.get_snake_color();

	LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Game Callback] Idle Game Callback for window ID: ", win_id);

	bool obs_eaten = contact_between_snake_obs();

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

		game_graphics::snake->add_node(new_snake_node_x, new_snake_node_y, node_width, node_height, snake_head_dir, color);

		int snake_units = snake_settings.get_snake_units();
		snake_settings.set_snake_units(snake_units + 1);

	} else {

		// Store speed locally because it can be changed anytime by the user. The update will be accounted for next time round
		int snake_speed = snake_settings.get_speed();

		game_graphics::snake->move(snake_speed, win_width, win_height, game_graphics::head_dir);

	}

	game_graphics::snake->check_collision(win_width, win_height);

	int win_id_new = glutGetWindow();
	if (win_id_new != 0) {
		LOG_INFO(logging::verb_level_e::DEBUG,"[Idle Game Callback] Idle Game Callback before glutPostRedisplay for window ID: ", win_id_new);
		// force glut to call the display function
		glutPostRedisplay();
	}

}

void game_graphics::wrapper_game_cb() {
	LOG_INFO(logging::verb_level_e::DEBUG,"[Game Graphics Wrapper] Enter game graphics wrapper");
	glutDisplayFunc( display_game_cb );
	glutKeyboardFunc( keyboard_game_cb );
	glutReshapeFunc( reshape_game_cb );
	glutIdleFunc( idle_game_cb );
	glutSpecialFunc( specialkey_game_cb );
	glutMouseFunc( mouse_game_cb );
}


void game_graphics::init_snake_list() {
	std::string name("Snake");
	game_graphics::snake = new snake_list::SnakeList(name);
	if (game_graphics::snake == nullptr) {
		LOG_ERROR("Can't allocate memory for snake list ", name, ".");
	}
}

void game_graphics::init_obstacle_list() {
	std::string name("Obstacle List");
	game_graphics::obstacles = new obstacle_list::ObstacleList(name);
	if (game_graphics::obstacles == nullptr) {
		LOG_ERROR("Can't allocate memory for obstacle list ", name, ".");
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
	graphics_utils::palette_e color = snake_settings.get_snake_color();

	for (int unit_no=0; unit_no < snake_units; unit_no++) {

		game_graphics::snake->add_node(centre_x, centre_y, node_width, node_height, head_dir, color);
		//game_graphics::snake->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, game_graphics::init_head_dir, (graphics_utils::palette_e) unit_no);
		centre_x += node_width;
		//game_graphics::snake->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, game_graphics::init_head_dir, graphics_utils::palette_e::RED);
		//centre_y += game_graphics::node_height;

	}

	// Colour snake_head differently to ease debug
	snake_node::SnakeNode * snake_head = game_graphics::snake->get_head();
	snake_head->set_colour(graphics_utils::palette_e::YELLOW);

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
	graphics_utils::palette_e color = snake_settings.get_obs_color();

	// Random coordinates must be within node_width/2 and (win_width-node_width/2)
	int centre_x = (rand() % (win_width_int - node_width)) + node_width/2;

	// Random coordinates must be within node_height/2 and (win_height-node_height/2)
	int centre_y = (rand() % (win_height_int - node_height)) + node_height/2;

	//game_graphics::obstacles->add_node(centre_x, centre_y, game_graphics::node_width, game_graphics::node_height, graphics_utils::palette_e::PURPLE);
	game_graphics::obstacles->add_node(centre_x, centre_y, node_width, node_height, color);
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

	save.write_ofile("Speed: ", snake_settings.get_speed(), "\n");
	save.write_ofile("\n");

	while (curr_snake_node != nullptr) {
		int node_x = curr_snake_node->get_x_centre();
		int node_y = curr_snake_node->get_y_centre();
		int node_width = curr_snake_node->get_width();
		int node_height = curr_snake_node->get_height();

		save.write_ofile("//******************************\n");
		save.write_ofile("// Snake Node ", snake_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		save.write_ofile("Type: Snake\n");
		save.write_ofile("X centre: ", node_x, "\n");
		save.write_ofile("Y centre: ", node_y, "\n");
		save.write_ofile("Width: ", node_width, "\n");
		save.write_ofile("Height: ", node_height, "\n");
		save.write_ofile("\n");

		// Save temporary obstacle
		curr_snake_node = curr_snake_node->get_next();
		snake_node_cnt++;
	}

	// obstacle pointer
	obstacle::ObstacleNode * curr_obs_node = game_graphics::obstacles->get_head();

	int obs_node_cnt = 0;

	while (curr_obs_node != nullptr) {
		int obs_x = curr_obs_node->get_x_centre();
		int obs_width = curr_obs_node->get_width();
		int obs_y = curr_obs_node->get_y_centre();
		int obs_height = curr_obs_node->get_height();

		save.write_ofile("//******************************\n");
		save.write_ofile("// Obstacle Node ", obs_node_cnt, "\n");
		save.write_ofile("//******************************\n");
		save.write_ofile("Type: Obstacle\n");
		save.write_ofile("X centre: ", obs_x, "\n");
		save.write_ofile("Y centre: ", obs_y, "\n");
		save.write_ofile("Width: ", obs_width, "\n");
		save.write_ofile("Height: ", obs_height, "\n");
		save.write_ofile("\n");


		// Save temporary obstacle
		curr_obs_node = curr_obs_node->get_next();
		obs_node_cnt++;
	}

}
