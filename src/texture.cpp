#include "graphics/texture.h"
#include "stb/stb.h"

using namespace cws::graphics;

std::list<GLuint> Texture::m_textures;

TextureSettings Texture::default_settings;

Texture::Texture()
{
	glGenTextures(1, &m_id);
	m_textures.push_back(m_id);
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::dispose() {
	m_textures.remove(m_id);
	glDeleteTextures(1, &m_id);	
}

void Texture::dispose_all() {
	for (auto& texture : m_textures) {
		glDeleteTextures(1, &texture);
	}
	m_textures.clear();
}

bool Texture::load_image(const char* filename, TextureSettings& settings) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.mag_filter);

	int width, height, num_channels;

	stbi_set_flip_vertically_on_load(settings.flip);
	unsigned char* data = stbi_load(filename, &width, &height, &num_channels, 0);

	GLenum format = (num_channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	return true;
}

bool Texture::load_color(glm::vec4 color) {
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = color.a * 255;
	
	unsigned char data[4] = { static_cast<unsigned char>(r),
                              static_cast<unsigned char>(g),
                              static_cast<unsigned char>(b),
                              static_cast<unsigned char>(a) };

	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return true;
}