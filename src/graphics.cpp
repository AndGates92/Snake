/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 11th February 2019
 * @brief Graphics functions
 */

#include <string>
#include <iostream>
#include <fstream>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"
#include "graphics.h"

using namespace std;
using namespace log;
using namespace graphics;

void graphics::init_gl(int argc, char** argv) {
	LOG_INFO(log::verb_level_e::ZERO, "Initialize GLUT");
	glutInit( &argc, argv );
}
