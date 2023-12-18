#ifndef CWS_VBO_H
#define CWS_VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <list>
#include <vector>

#include "data/vertex.h"

namespace cws::graphics {

	class VBO {
		public:
			VBO(GLenum buffer_type);
			
			void buffer_data(const void* data, GLsizei size_in_bytes);

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