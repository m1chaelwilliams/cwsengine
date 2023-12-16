#include "vbo.h"
#include "debug.h"

using namespace cws::graphics;

std::list<GLuint> VBO::m_vbos;

VBO::VBO(GLenum buffer_type) :
	m_type(buffer_type)
{
	glGenBuffers(1, &m_id);
	m_vbos.push_back(m_id);
}

void VBO::bind() {
	glBindBuffer(m_type, m_id);
}

void VBO::buffer_data(const void* data, GLsizei size_in_bytes) {
	glBufferData(m_type, size_in_bytes, data, GL_STATIC_DRAW);
}


void VBO::dispose() {
	m_vbos.remove(m_id);
	glDeleteBuffers(1, &m_id);
}

GLenum VBO::get_type() const {
	return m_type;
}

GLuint VBO::get_id() const {
	return m_id;
}

void VBO::dispose_all() {
	CWS_LOGLN("--- Deleting VAOs ---");

	for (auto& vbo : m_vbos) {
		glDeleteBuffers(1, &vbo);

		CWS_LOGLN("- Deleted VBO");
	}
	m_vbos.clear();
}