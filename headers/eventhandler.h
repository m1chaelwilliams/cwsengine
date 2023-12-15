#ifndef CWS_EVENTHANDLER_H
#define CWS_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace cws::io {

	class EventHandler {

		public:
			EventHandler();

			void on_event(int key, int action, int scancode);
			bool is_key_down(int key);
			bool is_key_pressed(int key);
		private:
			std::unordered_map<int, bool> m_keys_held;
			std::unordered_map<int, bool> m_keys_pressed;
	};

};

#endif