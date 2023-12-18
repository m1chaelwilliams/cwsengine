#ifndef CWS_VAO_H
#define CWS_VAO_H

#include <glad/glad.h>
#include <list>

namespace cws::graphics {

	class VAO {
		public:
			VAO();
			void bind();
			void link_buffer(int location, int size, int stride, int offset);
			GLuint get_id() const;

			static void unbind();

			void dispose();
			static void dispose_all();
		private:
			GLuint m_id;

			static std::list<GLuint> m_vaos;
	};

};

#endif