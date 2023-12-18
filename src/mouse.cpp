#include "io/mouse.h"
#include "utils/debug.h"

using namespace cws::io;

float Mouse::x = 0.0f;
float Mouse::y = 0.0f;

int Mouse::scroll = 0;

GLFWwindow* Mouse::m_window_context = nullptr;
MouseState Mouse::m_mouse_state = MouseState::NORMAL;

std::unordered_map<int, bool> Mouse::m_buttons_held;
std::unordered_map<int, bool> Mouse::m_buttons_pressed;

void Mouse::on_cursor_move_callback(GLFWwindow* window_ptr, double x, double y) {
	Mouse::x = x;
	Mouse::y = y;
}

void Mouse::on_mouse_button_callback(GLFWwindow* window_ptr, int key, int action, int mods) {
	switch(action) {

		case GLFW_RELEASE:
			m_buttons_held[key] = false;

			break;
		case GLFW_PRESS:
			m_buttons_pressed[key] = true;
			m_buttons_held[key] = true;	

			break;

	}
}

void Mouse::on_scroll_wheel_callback(GLFWwindow* window_ptr, double x_offset, double y_offset) {
	scroll = (int)y_offset;
}

bool Mouse::is_button_held(int key) {
	auto it = m_buttons_held.find(key);

	if (it != m_buttons_held.end() && it->second) {
		return true;
	}
	return false;
}

bool Mouse::is_button_pressed(int key) {
	auto it = m_buttons_pressed.find(key);

	if (it != m_buttons_pressed.end() && it->second) {
		it->second = false;
		return true;
	}
	return false;
}

void Mouse::set_mouse_state(MouseState state) {
	m_mouse_state = state;
	
	switch (state) {
		case MouseState::NORMAL:
			glfwSetInputMode(m_window_context, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case MouseState::GRABBED:
			glfwSetInputMode(m_window_context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
	}
}

MouseState Mouse::get_mouse_state() {
	return m_mouse_state;
}

int Mouse::get_scroll() {
	int result = scroll;

	return result;
}