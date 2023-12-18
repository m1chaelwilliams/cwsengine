#ifndef CWS_SHADERPROGRAM_H
#define CWS_SHADERPROGRAM_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <list>
#include <map>

#include "graphics/shader.h"

namespace cws::graphics {

	class ShaderProgram {
		public:
			ShaderProgram();
			void attach_shader(const Shader& shader);
			bool link_program();
			void use_program();
			void dispose();
			GLint find_uniform(const char* uniform_name);
			bool put_uniform_float(const char* uniform_name, float value);
			bool put_uniform_vec2(const char* uniform_name, const glm::vec2& vec);
			bool put_uniform_vec3(const char* uniform_name, const glm::vec3& vec);
			bool put_uniform_mat4(const char* uniform_name, const glm::mat4& mat, bool transpose = GL_FALSE);
			bool put_uniform_mat3(const char* uniform_name, const glm::mat3& mat, bool transpose = GL_FALSE);

			static void dispose_all();
		private:
			GLuint m_id;
			std::list<GLuint> m_shaders;
			std::map<std::string, GLint> m_uniforms;

			static std::list<GLuint> m_programs;
	};

};

#endif