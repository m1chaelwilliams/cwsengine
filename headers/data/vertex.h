#ifndef CWS_VERTEX_H
#define CWS_VERTEX_H

#include <glm/glm.hpp>

namespace cws::data {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};

};

#endif