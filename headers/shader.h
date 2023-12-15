#ifndef CWS_SHADER_H
#define CWS_SHADER_H

#include <glad/glad.h>
#include <map>
#include <list>

#include "fileutils.h"

namespace cws::graphics {

	class Shader {
		public:
			Shader(GLenum shader_type);
			bool load_shader_source(const char* shader_source);
			GLuint get_id() const;
			GLenum get_type() const;
			void dispose();

			static void dispose_all();
		private:
			GLenum m_type;
			GLuint m_id;

			static std::list<GLuint> m_shaders;
	};

};

#endif