#ifndef CWS_EVENTHANDLER_H
#define CWS_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace cws {
	class IApp;
}

namespace cws::io {

	class Keyboard {
		public:
			static bool is_key_down(int key);
			static bool is_key_pressed(int key);
		private:
			static void on_event(GLFWwindow* window_ptr, int key, int scancode, int action, int mods);

			static std::unordered_map<int, bool> m_keys_held;
			static std::unordered_map<int, bool> m_keys_pressed;

			friend class cws::IApp;
	};

};

#endif