#ifndef CWS_MESH_H
#define CWS_MESH_H

#include <glad/glad.h>
#include <vector>

#include "data/vertex.h"

namespace cws::models {

	class Mesh {
		public:
			Mesh();
			Mesh(
				const std::vector<data::Vertex>& vertices,
				const std::vector<GLuint>& indices
			);
			GLuint get_vao() const {return m_vao;}
			GLuint get_ebo() const {return m_ebo;}
			GLuint get_vertex_count() const {return m_vertex_count;}
			
			// getters
			const std::vector<data::Vertex>& get_vertices() const;
			const std::vector<GLuint>& get_indices() const;
		private:
			std::vector<data::Vertex> m_vertices;
			std::vector<GLuint> m_indices;
			GLuint m_vao, m_ebo, m_vertex_count;
	};
};

#endif