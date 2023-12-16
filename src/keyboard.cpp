#include "io/keyboard.h"

using namespace cws::io;

std::unordered_map<int, bool> Keyboard::m_keys_held;
std::unordered_map<int, bool> Keyboard::m_keys_pressed;

void Keyboard::on_event(GLFWwindow* window_ptr, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		m_keys_pressed[key] = true;
		m_keys_held[key] = true;
	} else if (action == GLFW_RELEASE) {
		m_keys_held[key] = false;
	}
}

bool Keyboard::is_key_down(int key) {
	auto it = m_keys_held.find(key);

	if (it != m_keys_held.end() && it->second) {
		return true;
	}
	return false;
}

bool Keyboard::is_key_pressed(int key) {
	auto it = m_keys_pressed.find(key);

	if (it != m_keys_pressed.end() && it->second) {
		return true;
	}
	return false;
}