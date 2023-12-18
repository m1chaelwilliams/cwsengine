#include "graphics/renderer.h"

using namespace cws::graphics;

Renderer::Renderer() {

}

void Renderer::clear(glm::vec4 clear_color, GLbitfield mask) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(mask);
}

void Renderer::render(const models::Mesh& mesh) {
	glBindVertexArray(mesh.get_vao());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.get_ebo());
	glDrawElements(GL_TRIANGLES, mesh.get_vertex_count(), GL_UNSIGNED_INT, 0);
}

void Renderer::render(ShaderProgram& program, const models::RawModel& model) {
	program.use_program();

	glm::mat4 model_mat = glm::mat4(1.0f);

	model_mat = glm::translate(model_mat, model.position);

	model_mat = glm::rotate(model_mat, glm::radians(model.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model_mat = glm::rotate(model_mat, glm::radians(model.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model_mat = glm::rotate(model_mat, glm::radians(model.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model_mat = glm::scale(model_mat, model.scale);

	program.put_uniform_mat4("model", model_mat);

	for (const auto& mesh : model.get_meshes()) {
		render(mesh);
	}
}

void Renderer::render(ShaderProgram& program, const models::TexturedModel& model) {
	model.get_texture().bind();

	render(program, model.get_raw_model());
}