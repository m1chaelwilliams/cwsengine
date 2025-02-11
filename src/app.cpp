#include "core/app.h"
#include "io/io.h"

#include <typeinfo>

using namespace cws;

IApp::IApp(settings::WindowSettings& settings) :
	m_window_ptr(nullptr),
	m_width(settings.width),
	m_height(settings.height),
	m_title(settings.title)
{}

IApp::IApp() :
	m_window_ptr(nullptr)
{
	settings::WindowSettings settings;
	
	m_width = settings.width;
	m_height = settings.height;
	m_title = settings.title;
}

IApp::~IApp() {}

int IApp::run() {
	CWS_LOGLN("--- Starting application... ---");

	if (!(init_window() && init_graphics())) {
		return false;
	}

	on_load();

	CWS_LOGLN("Entering main loop...");

	while (!glfwWindowShouldClose(m_window_ptr) && !scene_manager.is_empty()) {
		glfwPollEvents();
		
		on_update();

		io::Keyboard::m_keys_pressed.clear();
		io::Mouse::m_buttons_pressed.clear();
		io::Mouse::scroll = 0;

		on_draw();

		glfwSwapBuffers(m_window_ptr);
	}

	CWS_LOGLN("Leaving main loop...");

	on_unload();

	clean_up();

	return 0;
}

bool IApp::init_window() {
	if (!glfwInit()) {
		return false;
	}

	m_window_ptr = glfwCreateWindow(
		m_width,
		m_height,
		m_title,
		nullptr,
		nullptr
	);

	if (!m_window_ptr) {
		glfwTerminate();
		return false;
	}

	io::Mouse::m_window_context = m_window_ptr;

	glfwSetWindowUserPointer(m_window_ptr, this);
	glfwSetFramebufferSizeCallback(m_window_ptr, on_frame_buffer_size_callback);
	glfwSetKeyCallback(m_window_ptr, io::Keyboard::on_event);
	glfwSetCursorPosCallback(m_window_ptr, io::Mouse::on_cursor_move_callback);
	glfwSetMouseButtonCallback(m_window_ptr, io::Mouse::on_mouse_button_callback);
	glfwSetScrollCallback(m_window_ptr, io::Mouse::on_scroll_wheel_callback);

	CWS_LOGLN("Init window success!");

	return true;
}

bool IApp::init_graphics() {
	glfwMakeContextCurrent(m_window_ptr);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Adjust version as needed
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return false;
    }

	CWS_LOGLN("Init OpenGL success!");

	return true;
}

void IApp::clean_up() {
	CWS_LOGLN("Disposing graphics...");

	graphics::VAO::dispose_all();
	graphics::VBO::dispose_all();
	graphics::Shader::dispose_all();
	graphics::ShaderProgram::dispose_all();
	graphics::Texture::dispose_all();

	// unload internals
	scene_manager.clear();

	CWS_LOGLN("Disposing window...");

	// unload glfw
	glfwDestroyWindow(m_window_ptr);
	glfwTerminate();
}

void IApp::on_update() {}

void IApp::on_draw() {}

void IApp::on_frame_buffer_size_callback(GLFWwindow* window_ptr, int width, int height) {
	IApp* instance = static_cast<IApp*>(glfwGetWindowUserPointer(window_ptr));

	instance->on_resize(width, height);
}

// utils

void IApp::close() {
	glfwSetWindowShouldClose(m_window_ptr, 1);
}