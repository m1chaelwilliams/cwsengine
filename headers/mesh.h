#ifndef CWS_MESH_H
#define CWS_MESH_H

#include <glad/glad.h>

namespace cws::data {

	class Mesh {
		public:
			Mesh(
				GLuint vao,
				GLuint position_vbo,
				GLuint texture_vbo,
				GLsizei vertex_count
			) :
				m_vao(vao),
				m_position_vbo(position_vbo),
				m_texture_vbo(texture_vbo),
				m_vertex_count(vertex_count)
			{}

		GLuint get_vao() const;
		GLuint get_position_vbo() const;
		GLuint get_texture_vbo() const;
		GLsizei get_vertex_count() const;

		private:
			GLuint m_vao;
			GLuint m_position_vbo;
			GLuint m_texture_vbo;
			GLsizei m_vertex_count;
	};

};

#endif