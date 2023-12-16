#ifndef CWS_EVENTHANDLER_H
#define CWS_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace cws::io {

	class Keyboard {

		public:
			static void on_event(GLFWwindow* window_ptr, int key, int scancode, int action, int mods);
			static bool is_key_down(int key);
			static bool is_key_pressed(int key);
		private:
			static std::unordered_map<int, bool> m_keys_held;
			static std::unordered_map<int, bool> m_keys_pressed;
	};

};

#endif