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

			// texture loading

			m_texture.load_image("assets/stone.png");

			m_red_tex.load_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

			cws::graphics::TextureSettings settings;

			settings.min_filter = GL_LINEAR;
			settings.mag_filter = GL_LINEAR;

			m_gun_tex.load_image("assets/models/cat/Cat_diffuse.jpg", settings);

			glEnable(GL_DEPTH_TEST);

			m_position = glm::vec3(0.0f, 0.0f, 0.0f);

			m_camera = new cws::world::Camera(
				glm::vec3(0.0f, 0.0f, 0.0f),
				90.0f
			);

			cws::io::Mouse::set_mouse_state(cws::io::MouseState::GRABBED);

			// loading meshes

			cws::models::Mesh cat_mesh = cws::models::ObjLoader::load_mesh("assets/models/cat/cat.obj");

			cws::models::RawModel model = cws::models::RawModel(cat_mesh);

			m_models.emplace_back(m_gun_tex, model);

		}
		void on_unload() override {

		}
		void on_update() override {
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_S)) {
				m_camera->position -= 0.02f * m_camera->get_front_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_W)) {
				m_camera->position += 0.02f * m_camera->get_front_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_A)) {
				m_camera->position -= 0.02f * m_camera->get_right_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_D)) {
				m_camera->position += 0.02f * m_camera->get_right_vector();
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_LEFT_SHIFT)) {
				m_camera->position.y -= 0.02f;
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_SPACE)) {
				m_camera->position.y += 0.02f;
			}
			if (cws::io::Keyboard::is_key_down(GLFW_KEY_Q)) {
				m_app_ptr->close();
			}
			if (cws::io::Keyboard::is_key_pressed(GLFW_KEY_ESCAPE)) {
				switch (cws::io::Mouse::get_mouse_state()) {
					case cws::io::MouseState::NORMAL:
						m_camera->set_last_mouse_pos(cws::io::Mouse::x, cws::io::Mouse::y);
						cws::io::Mouse::set_mouse_state(cws::io::MouseState::GRABBED);
						break;
					case cws::io::MouseState::GRABBED:
						cws::io::Mouse::set_mouse_state(cws::io::MouseState::NORMAL);
						break;
				}
			}

			if (cws::io::Mouse::is_button_pressed(GLFW_MOUSE_BUTTON_LEFT)) {
				CWS_LOGLN("Left click!");
			}
			if (cws::io::Mouse::get_scroll() == 1) {

				float current_fov = m_camera->get_fov();

				CWS_LOGLN(current_fov);

				float new_fov = current_fov + 1.0f;

				if (new_fov > 180.0f) {
					new_fov = 180.0f;
				}

				m_camera->set_fov(new_fov);
			}

			if (cws::io::Mouse::get_scroll() == -1) {

				float current_fov = m_camera->get_fov();

				CWS_LOGLN(current_fov);

				float new_fov = current_fov - 1.0f;

				if (new_fov < 10.0f) {
					new_fov = 10;
				}

				m_camera->set_fov(new_fov);
			}

			// CWS_LOGLN(m_camera->position.z);

			if (cws::io::Mouse::get_mouse_state() == cws::io::MouseState::GRABBED)
				m_camera->update(cws::io::Mouse::x, cws::io::Mouse::y);



			m_program.put_uniform_mat4("view", m_camera->get_view_matrix());
			m_program.put_uniform_mat4("projection", m_camera->get_projection_matrix());
			m_program.put_uniform_vec3("cam_pos", m_camera->position);

			m_program.put_uniform_vec3("lights[0].position", m_camera->position);
			m_program.put_uniform_vec3("lights[0].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
			m_program.put_uniform_vec3("lights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));
			m_program.put_uniform_vec3("lights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		}
		void on_draw() override {
			m_renderer.clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_gun_tex.bind();
			for (const auto& model : m_models) {
				m_renderer.render(m_program, model);
			}
		}
	private:
		glm::vec3 m_position;
		cws::IApp* m_app_ptr;
		cws::world::Camera* m_camera;
		cws::graphics::Renderer m_renderer;
		cws::graphics::Texture m_texture;
		cws::graphics::Texture m_red_tex;
		cws::graphics::Texture m_gun_tex;
		cws::graphics::ShaderProgram m_program;

		std::vector<cws::models::TexturedModel> m_models;

		float delta;
};

class ExampleApp : public cws::IApp {
	public:
		ExampleApp(cws::settings::WindowSettings& s) : IApp(s) {}
	protected:
		void on_load() override {
			scene_manager.push(new ExampleScene(this));
			scene_manager.peek()->on_load();
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