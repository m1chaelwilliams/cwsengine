#ifndef CWS_APP_H
#define CWS_APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scenemanager.h"
#include "windowconfig.h"
#include "eventhandler.h"

namespace cws {
	class IApp {
		public:
			SceneManager scene_manager;

			IApp(settings::WindowSettings& settings);
			IApp();
			~IApp();
			int run();

			// getters
			io::EventHandler* get_event_handler();
		protected:
			virtual void on_load() = 0;
			virtual void on_unload() = 0;
			virtual void on_update() = 0;
			virtual void on_draw() = 0;
			virtual void on_resize(int width, int height)
			{
				m_width = width;
				m_height = height;
			}
		private:
			bool init_window();
			bool init_graphics();
			void clean_up();

			// member vars
			GLFWwindow* m_window_ptr;
			int m_width, m_height;
			const char* m_title;
			// managers
			io::EventHandler m_event_handler;

			static void on_frame_buffer_size_callback(GLFWwindow* window_ptr, int width, int height);
			static void on_key_callback(GLFWwindow* window_ptr, int key, int scancode, int action, int mods);
	};

};

#endif