#include "model.h"

using namespace cws::renderdata;

RawModel::RawModel(
	const Mesh& mesh,
	glm::vec3 position,
	glm::vec3 rotation,
	glm::vec3 scale
) :
	mesh(mesh),
	position(position),
	rotation(rotation),
	scale(scale)
{}

