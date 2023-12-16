#include "io/mouse.h"

using namespace cws::io;

float Mouse::x = 0.0f;
float Mouse::y = 0.0f;

void Mouse::_on_cursor_move_callback(GLFWwindow* window_ptr, double x, double y) {
	Mouse::x = x;
	Mouse::y = y;
}