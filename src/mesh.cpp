#include "mesh.h"

using namespace cws::data;

GLuint Mesh::get_vao() const {
	return m_vao;
}

GLuint Mesh::get_position_vbo() const {
	return m_position_vbo;
}

GLuint Mesh::get_texture_vbo() const {
	return m_texture_vbo;
}

GLsizei Mesh::get_vertex_count() const {
	return m_vertex_count;
}