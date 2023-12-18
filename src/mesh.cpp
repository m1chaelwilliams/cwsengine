#include "models/mesh.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "utils/debug.h"

using namespace cws::models;

Mesh::Mesh() :
	m_vao(0),
	m_ebo(0),
	m_vertex_count(0)
{}

Mesh::Mesh(
	const std::vector<cws::data::Vertex>& vertices,
	const std::vector<GLuint>& indices
) :
	m_vertices(vertices),
	m_indices(indices)
{
	CWS_LOGLN("- Processing mesh");

	cws::graphics::VAO vao;
	vao.bind();
	
	cws::graphics::VBO vbo(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.buffer_data(vertices.data(), vertices.size() * sizeof(cws::data::Vertex));

	vao.link_buffer(0, 3, 8, 0);
	vao.link_buffer(1, 3, 8, 3);
	vao.link_buffer(2, 2, 8, 6);

	cws::graphics::VBO ebo(GL_ELEMENT_ARRAY_BUFFER);
	ebo.bind();
	ebo.buffer_data(indices.data(), indices.size() * sizeof(GLuint));

	m_vao = vao.get_id();
	m_ebo = ebo.get_id();
	m_vertex_count = indices.size();
}

const std::vector<cws::data::Vertex>& Mesh::get_vertices() const {
	return m_vertices;
}

const std::vector<GLuint>& Mesh::get_indices() const {
	return m_indices;
}