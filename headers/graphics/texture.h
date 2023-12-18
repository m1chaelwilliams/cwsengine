#ifndef CWS_TEXTURE_H
#define CWS_TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <list>

namespace cws::graphics {

	struct TextureSettings {
		int flip;
		GLenum wrap_s, wrap_t, min_filter, mag_filter;

		TextureSettings(
			int flip = 1,
			GLenum wrap_s = GL_REPEAT,
			GLenum wrap_t = GL_REPEAT,
			GLenum min_filter = GL_NEAREST,
			GLenum mag_filter = GL_NEAREST
		) :
			flip(flip),
			wrap_s(wrap_s),
			wrap_t(wrap_t),
			min_filter(min_filter),
			mag_filter(mag_filter)
		{}
	};

	class Texture {
		public:
			static TextureSettings default_settings;

			Texture();
			bool load_image(const char* filename, TextureSettings& settings = default_settings);
			bool load_color(glm::vec4 color);
			void bind() const;

			static void unbind();
			void dispose();
			static void dispose_all();
		private:
			GLuint m_id;

			static std::list<GLuint> m_textures;
	};

};

#endif