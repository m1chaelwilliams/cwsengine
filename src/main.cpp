#include "cws.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleScene : public cws::IScene {
	public:
		ExampleScene(cws::IApp* app_ptr) : 
			m_app_ptr(app_ptr)
		{}
		void on_load() override {
			cws::graphics::Shader v_shader(GL_VERTEX_SHADER);
			const char* v_source = cws::utils::read_file_contents("shaders/3d.vert").c_str();
			v_shader.load_shader_source(v_source);

			cws::graphics::Shader f_shader(GL_FRAGMENT_SHADER);
			const char* f_source = cws::utils::read_file_contents("shaders/3d.frag").c_str();
			f_shader.load_shader_source(f_source);

			m_program.attach_shader(v_shader);
			m_program.attach_shader(f_shader);

			m_program.link_program();

			m_program.use_program();

			std::vector<cws::renderdata::Vertex> vertices = {
				cws::renderdata::Vertex{glm::vec3(-0.5, 0.5, 0.0f), glm::vec3(), glm::vec2(0.0f, 0.0f)},
				cws::renderdata::Vertex{glm::vec3(0.5, 0.5, 0.0f), glm::vec3(), glm::vec2(1.0f, 0.0f)},
				cws::renderdata::Vertex{glm::vec3(0.5, -0.5, 0.0f), glm::vec3(), glm::vec2(1.0f, 1.0f)},
				cws::renderdata::Vertex{glm::vec3(-0.5, -0.5, 0.0f), glm::vec3(), glm::vec2(0.0f, 1.0f)}
			};

			std::vector<GLuint> indices = {
				0,1,2,
				2,3,0
			};
		
			m_plane = new cws::renderdata::Mesh(
				vertices,
				indices
			);

			m_model = new cws::renderdata::RawModel(
				*m_plane,
				glm::vec3(0.0f, 0.0f, 2.0f)
			);

			m_model2 = new cws::renderdata::RawModel(
				*m_plane,
				glm::vec3(0.0f, -2.0f, -2.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(10.0f, 10.0f, 10.0f)
			);

			m_model_mat = glm::mat4(1.0f);

			// texture loading

			cws::graphics::TextureSettings settings;

			m_texture.config(settings);
			m_texture.load_image("assets/stone.png");

			glEnable(GL_DEPTH_TEST);

			m_position = glm::vec3(0.0f, 0.0f, 0.0f);

			m_camera = new cws::world::Camera(
				glm::vec3(0.0f, 0.0f, 0.0f),
				90.0f
			);
		}
		void on_unload() override {
			delete m_plane;
			delete m_model;
			delete m_model2;
			delete m_camera;
		}
		void on_update() override {
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_S)) {
				m_camera->position -= 0.01f * m_camera->get_front_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_W)) {
				m_camera->position += 0.01f * m_camera->get_front_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_A)) {
				m_camera->position -= 0.01f * m_camera->get_right_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_D)) {
				m_camera->position += 0.01f * m_camera->get_right_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_LEFT_SHIFT)) {
				m_camera->position.y -= 0.01f;
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_SPACE)) {
				m_camera->position.y += 0.01f;
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_Q)) {
				m_app_ptr->close();
			}

			m_camera->update(cws::io::Mouse::x, cws::io::Mouse::y);

			CWS_LOGLN(cws::io::Mouse::x << " " << cws::io::Mouse::y);

			m_program.put_uniform_mat4("view", m_camera->get_view_matrix());
			m_program.put_uniform_mat4("projection", m_camera->get_projection_matrix());
		}
		void on_draw() override {
			m_renderer.clear(glm::vec4(0.4f, 0.6f, 1.0f, 1.0f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_texture.bind();
			m_renderer.render(m_program, *m_model);
			m_renderer.render(m_program, *m_model2);
			// m_renderer.render(m_program, *m_plane);
		}
	private:
		glm::vec3 m_position;
		cws::IApp* m_app_ptr;
		cws::world::Camera* m_camera;
		cws::graphics::Renderer m_renderer;
		cws::graphics::Texture m_texture;
		cws::renderdata::Mesh* m_plane;
		cws::renderdata::RawModel* m_model;
		cws::renderdata::RawModel* m_model2;
		glm::mat4 m_model_mat;
		glm::mat4 m_view_mat;
		glm::mat4 m_projection_mat;
		cws::graphics::ShaderProgram m_program;

		float delta;
};

class ExampleApp : public cws::IApp {
	public:
		ExampleApp(cws::settings::WindowSettings& s) : IApp(s) {}
	protected:
		void on_load() override {
			scene_manager.push(new ExampleScene(this));
			scene_manager.peek()->on_load();

			glfwSetInputMode(m_window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		void on_unload() override {
			scene_manager.peek()->on_unload();
		}
		void on_resize(int width, int height) override {
			IApp::on_resize(width, height);
			glViewport(0,0, width, height);
		}
		void on_update() override {
			cws::IScene* active_scene_ptr = scene_manager.peek();
			if (active_scene_ptr)
				active_scene_ptr->on_update();
		}
		void on_draw() override {
			cws::IScene* active_scene_ptr = scene_manager.peek();
			if (active_scene_ptr)
				active_scene_ptr->on_draw();
		}
};

int main() {
	cws::settings::WindowSettings settings;
	settings.width = 1280;
	settings.height = 720;

	return ExampleApp(settings).run();
}