#ifndef CWS_VBO_H
#define CWS_VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <list>

namespace cws::graphics {

	class VBO {
		public:
			VBO(GLenum buffer_type);
			
			void buffer_data(GLuint* data, GLsizei size_in_bytes);
			void buffer_data(float* data, GLsizei size_in_bytes);
			void buffer_data(glm::vec2* data, GLsizei size_in_bytes);
			void buffer_data(glm::vec3* data, GLsizei size_in_bytes);
			void buffer_data(glm::vec4* data, GLsizei size_in_bytes);

			void bind();

			GLenum get_type() const;
			GLuint get_id() const;

			static void unbind();
			void dispose();
			static void dispose_all();
		private:
			GLuint m_id;
			GLenum m_type;

			static std::list<GLuint> m_vbos;
	};

};

#endif