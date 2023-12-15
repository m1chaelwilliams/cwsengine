#include "vao.h"
#include "debug.h"

using namespace cws::graphics;

std::list<GLuint> VAO::m_vaos;

VAO::VAO() {
	glGenVertexArrays(1, &m_id);
	m_vaos.push_back(m_id);
}

void VAO::bind() {
	glBindVertexArray(m_id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

GLuint VAO::get_id() const {
	return m_id;
}

void VAO::dispose() {
	m_vaos.remove(m_id);
	glDeleteVertexArrays(1, &m_id);
}

void VAO::dispose_all() {
	CWS_LOGLN("--- Deleting VAOs... ---");

	for (auto& vao : m_vaos) {
		glDeleteVertexArrays(1, &vao);

		CWS_LOGLN("- Deleted VAO");
	}
	m_vaos.clear();
}

void VAO::link_buffer(int location, int size, int stride, int offset) {
	glVertexAttribPointer(
		location,
		size,
		GL_FLOAT,
		false,
		stride * sizeof(GLfloat),
		(void*)(offset * sizeof(GLfloat))
	);

	glEnableVertexAttribArray(location);
}