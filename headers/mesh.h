#ifndef CWS_MESH_H
#define CWS_MESH_H

#include <glad/glad.h>
#include <vector>

#include "vertex.h"

namespace cws::renderdata {

	class Mesh {
		public:
			Mesh(
				std::vector<Vertex>& vertices,
				std::vector<GLuint>& indices
			);
			GLuint get_vao() const {return m_vao;}
			GLuint get_ebo() const {return m_ebo;}
			GLuint get_vertex_count() const {return m_vertex_count;}
		private:
			std::vector<Vertex> m_vertices;
			std::vector<GLuint> m_indices;
			GLuint m_vao, m_ebo, m_vertex_count;
	};

};

#endif