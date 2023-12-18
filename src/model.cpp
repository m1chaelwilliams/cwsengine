#include "models/model.h"

using namespace cws::models;

RawModel::RawModel(
	const Mesh& mesh,
	const Transform& transform
) :
	position(transform.position),
	rotation(transform.rotation),
	scale(transform.scale)
{
	m_meshes.push_back(mesh);
}

RawModel::RawModel(
	const std::vector<Mesh>& meshes,
	const Transform& transform
) :
	m_meshes(meshes),
	position(transform.position),
	rotation(transform.rotation),
	scale(transform.scale)
{}

void RawModel::add_mesh(const Mesh& mesh) {
	m_meshes.push_back(mesh);
}

// getters

const std::vector<Mesh>& RawModel::get_meshes() const {
	return m_meshes;
}

TexturedModel::TexturedModel(
	const cws::graphics::Texture& texture,
	const RawModel& model
) :
	m_texture(texture),
	m_model(model)
{}

const cws::graphics::Texture& TexturedModel::get_texture() const {
	return m_texture;
}

const RawModel& TexturedModel::get_raw_model() const {
	return m_model;
}