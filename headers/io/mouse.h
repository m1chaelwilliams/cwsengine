#ifndef CWS_MOUSE_H
#define CWS_MOUSE_H

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace cws {
	class IApp;
}

namespace cws::io {

	enum class MouseState {
		NORMAL,
		GRABBED
	};

	class Mouse {
		public:
			static float x;
			static float y;

			static bool is_button_pressed(int key);
			static bool is_button_held(int key);
			static int get_scroll();

			static void set_mouse_state(MouseState state);
			static MouseState get_mouse_state();
	
		private:
			static void on_cursor_move_callback(GLFWwindow* window_ptr, double x, double y);
			static void on_mouse_button_callback(GLFWwindow* window_ptr, int button, int action, int mods);
			static void on_scroll_wheel_callback(GLFWwindow* window_ptr, double x_offset, double y_offset);

			static GLFWwindow* m_window_context;
			static MouseState m_mouse_state;

			static std::unordered_map<int, bool> m_buttons_pressed;
			static std::unordered_map<int, bool> m_buttons_held;
			static int scroll;

			friend class cws::IApp;
	};

};

#endif