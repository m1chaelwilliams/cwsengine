#include "texture.h"
#include "stb/stb.h"

using namespace cws::graphics;

std::list<GLuint> Texture::m_textures;

Texture::Texture()
{
	glGenTextures(1, &m_id);
	m_textures.push_back(m_id);
}

void Texture::config(TextureSettings& settings) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.mag_filter);
}

void Texture::bind() {
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

bool Texture::load_image(const char* filename) {
	bind();

	int width, height, num_channels;

	unsigned char* data = stbi_load(filename, &width, &height, &num_channels, 0);

	GLenum format = (num_channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	return true;
}