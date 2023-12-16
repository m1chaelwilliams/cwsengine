#ifndef CWS_MOUSE_H
#define CWS_MOUSE_H

#include <GLFW/glfw3.h>

namespace cws::io {

	class Mouse {
		public:
			static float x;
			static float y;

			static void _on_cursor_move_callback(GLFWwindow* window_ptr, double x, double y);
	};

};

#endif