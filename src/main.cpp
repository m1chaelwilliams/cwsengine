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

			GLfloat vertices[] = {
				-0.5f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,

				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
			};

			GLfloat uv[] = {
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,

				1.0f, 1.0f,
				0.0f, 1.0f,
				0.0f, 0.0f
			};

			
			cws::graphics::VAO vao;
			vao.bind();

			cws::graphics::VBO vbo(GL_ARRAY_BUFFER);
			vbo.bind();
			vbo.buffer_data(vertices, sizeof(vertices));

			vao.link_buffer(0, 3, 0, 0);

			cws::graphics::VBO uv_vbo(GL_ARRAY_BUFFER);
			uv_vbo.bind();
			uv_vbo.buffer_data(uv, sizeof(uv));

			vao.link_buffer(1, 2, 0, 0);
			

			m_plane = new cws::data::Mesh(
				vao.get_id(),
				vbo.get_id(),
				uv_vbo.get_id(),
				sizeof(vertices) / sizeof(float)
			);


			m_model_mat = glm::mat4(1.0f);

			// texture loading

			cws::graphics::TextureSettings settings;

			m_texture.config(settings);
			m_texture.load_image("assets/stone.png");

			glEnable(GL_DEPTH_TEST);
		}
		void on_unload() override {
			delete m_plane;

			cws::graphics::Shader::dispose_all();
			cws::graphics::ShaderProgram::dispose_all();
			cws::graphics::VAO::dispose_all();
			cws::graphics::VBO::dispose_all();
			cws::graphics::Texture::dispose_all();
		}
		void on_update() override {
			if (m_app_ptr->get_event_handler()->is_key_down(GLFW_KEY_DOWN)) {
				CWS_LOGLN("moving backwards");
				m_position.z -= 0.01f;
			}
			if (m_app_ptr->get_event_handler()->is_key_down(GLFW_KEY_UP)) {
				CWS_LOGLN("moving forwards");
				m_position.z += 0.01f;
			}

			m_model_mat = glm::rotate(m_model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			// m_model_mat = glm::translate(m_model_mat, glm::vec3(0.001f, 0.0f, 0.0f));
			
			m_view_mat = glm::lookAt(
				m_position,
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)
			);

			m_projection_mat = glm::perspective(
				glm::radians(90.0f),
				600.0f / 400.0f,
				0.1f,
				100.0f
			);

			m_program.put_uniform_mat4("model", m_model_mat);
			m_program.put_uniform_mat4("view", m_view_mat);
			m_program.put_uniform_mat4("projection", m_projection_mat);
		}
		void on_draw() override {
			glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			m_renderer.clear(glm::vec4(0.4f, 0.6f, 1.0f, 1.0f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_texture.bind();
			m_renderer.render(*m_plane);
		}
	private:
		glm::vec3 m_position;
		cws::IApp* m_app_ptr;
		cws::graphics::Renderer m_renderer;
		cws::graphics::Texture m_texture;
		cws::data::Mesh* m_plane;
		glm::mat4 m_model_mat;
		glm::mat4 m_view_mat;
		glm::mat4 m_projection_mat;
		cws::graphics::ShaderProgram m_program;
};

class ExampleApp : public cws::IApp {
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
	return ExampleApp().run();
}