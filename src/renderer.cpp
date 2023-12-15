#include "renderer.h"

using namespace cws::graphics;

Renderer::Renderer() {

}

void Renderer::clear(glm::vec4 clear_color, GLbitfield mask) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(mask);
}

void Renderer::render(const data::Mesh& mesh) {
	glBindVertexArray(mesh.get_vao());
	glDrawArrays(GL_TRIANGLES, 0, mesh.get_vertex_count());
}