#ifndef CWS_TEXTURE_H
#define CWS_TEXTURE_H

#include <glad/glad.h>
#include <list>

namespace cws::graphics {

	struct TextureSettings {
		GLenum wrap_s, wrap_t, min_filter, mag_filter;

		TextureSettings(
			GLenum wrap_s = GL_REPEAT,
			GLenum wrap_t = GL_REPEAT,
			GLenum min_filter = GL_NEAREST,
			GLenum mag_filter = GL_NEAREST
		) :
			wrap_s(wrap_s),
			wrap_t(wrap_t),
			min_filter(min_filter),
			mag_filter(mag_filter)
		{}
	};

	class Texture {
		public:
			Texture();
			void config(TextureSettings& settings);
			bool load_image(const char* filename);
			void bind();

			static void unbind();
			void dispose();
			static void dispose_all();
		private:
			GLuint m_id;

			static std::list<GLuint> m_textures;
	};

};

#endif