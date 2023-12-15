#include "eventhandler.h"

using namespace cws::io;

EventHandler::EventHandler() {}

void EventHandler::on_event(int key, int action, int scancode) {
	if (action == GLFW_PRESS) {
		m_keys_pressed[key] = true;
		m_keys_held[key] = true;
	} else if (action == GLFW_RELEASE) {
		m_keys_held[key] = false;
	}
}

bool EventHandler::is_key_down(int key) {
	auto it = m_keys_held.find(key);

	if (it != m_keys_held.end() && it->second) {
		return true;
	}
	return false;
}

bool EventHandler::is_key_pressed(int key) {
	auto it = m_keys_pressed.find(key);

	if (it != m_keys_pressed.end() && it->second) {
		return true;
	}
	return false;
}