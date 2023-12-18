#include "graphics/shader.h"
#include "utils/debug.h"

using namespace cws::graphics;

std::list<GLuint> Shader::m_shaders;

Shader::Shader(GLenum type) :
	m_type(type),
	m_id(0)
{
	m_id = glCreateShader(m_type);
	m_shaders.push_back(m_id);
}

bool Shader::load_shader_source(const char* shader_source) {
	glShaderSource(m_id, 1, &shader_source, nullptr);
	glCompileShader(m_id);

	GLint compile_status;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_status);

	if (compile_status != GL_TRUE) {
		CWS_LOGLN("CRITICAL: FAILED TO LOAD SHADER");
		m_shaders.remove(m_id);
		glDeleteShader(m_id);
		return false;
	}
	CWS_LOGLN("Shader source loaded successfully!");

	return true;
}

GLuint Shader::get_id() const {
	return m_id;
}

GLenum Shader::get_type() const {
	return m_type;
}

void Shader::dispose() {
	m_shaders.remove(m_id);
	glDeleteShader(m_id);
}

void Shader::dispose_all() {
	for (auto& s_id : m_shaders) {
		glDeleteShader(s_id);
	}
	m_shaders.clear();
}