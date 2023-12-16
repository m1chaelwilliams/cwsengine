#include "shaderprogram.h"
#include "debug.h"
#include <glm/gtc/type_ptr.hpp>

using namespace cws::graphics;

std::list<GLuint> ShaderProgram::m_programs;

ShaderProgram::ShaderProgram() {
	m_id = glCreateProgram();
	m_programs.push_back(m_id);
}

void ShaderProgram::attach_shader(const Shader& shader) {
	glAttachShader(m_id, shader.get_id());
	m_shaders.push_back(shader.get_id());
}

bool ShaderProgram::link_program() {
	glLinkProgram(m_id);

	GLint link_status;
	glGetProgramiv(m_id, GL_LINK_STATUS, &link_status);

	if (link_status != GL_TRUE) {
		CWS_LOGLN("CRITICAL: FAILED TO LINK PROGRAM");
		m_programs.remove(m_id);
		glDeleteProgram(m_id);
		return false;
	}
	CWS_LOGLN("Shader Program link success!");

	for (auto& shader : m_shaders) {
		glDetachShader(m_id, shader);
	}

	return true;
}

void ShaderProgram::use_program() {
	glUseProgram(m_id);
}

void ShaderProgram::dispose() {
	m_programs.remove(m_id);
	glDeleteProgram(m_id);
}

void ShaderProgram::dispose_all() {
	for (auto& program : m_programs) {
		glDeleteProgram(program);
	}
	m_programs.clear();
}

GLint ShaderProgram::find_uniform(const char* uniform_name) {
	auto it = m_uniforms.find(uniform_name);
	if (it != m_uniforms.end()) {
		return it->second;
	}

	GLint uniform_location = glGetUniformLocation(m_id, uniform_name);
	if (uniform_location == -1) {
		CWS_LOGLN("Uniform: " << uniform_name << " not found!");
		return -1;
	}

	m_uniforms[uniform_name] = uniform_location;

	return uniform_location;
}

bool ShaderProgram::put_uniform_mat3(const char* uniform_name, const glm::mat3& mat) {
	GLint uniform_location = find_uniform(uniform_name);
	if (uniform_location == -1) {
		CWS_LOGLN("Failed to find uniform: " << uniform_name);
		return false;
	}

	glUniformMatrix3fv(uniform_location, 1, GL_TRUE, glm::value_ptr(mat));
	return true;
}

bool ShaderProgram::put_uniform_mat4(const char* uniform_name, const glm::mat4& mat) {
	GLint uniform_location = find_uniform(uniform_name);
	if (uniform_location == -1) {
		CWS_LOGLN("Failed to find uniform: " << uniform_name);
		return false;
	}

	glUniformMatrix4fv(uniform_location, 1, GL_TRUE, glm::value_ptr(mat));
	return true;
}