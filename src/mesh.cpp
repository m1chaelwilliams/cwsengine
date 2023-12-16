#include "mesh.h"
#include "vao.h"
#include "vbo.h"

using namespace cws::renderdata;

Mesh::Mesh(
	std::vector<Vertex>& vertices,
	std::vector<GLuint>& indices
) :
	m_vertices(vertices),
	m_indices(indices)
{

	cws::graphics::VAO vao;
	vao.bind();
	
	cws::graphics::VBO vbo(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.buffer_data(vertices.data(), vertices.size() * sizeof(Vertex));

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