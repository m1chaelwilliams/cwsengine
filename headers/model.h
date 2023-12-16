#ifndef CWS_MODEL_H
#define CWS_MODEL_H

#include "mesh.h"

namespace cws::renderdata {

	class RawModel {
		public:
			RawModel(
				const Mesh& mesh,
				glm::vec3 position = glm::vec3(),
				glm::vec3 rotation = glm::vec3(),
				glm::vec3 scale = glm::vec3(1.0f)
			);

			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			Mesh mesh;
	};

};

#endif