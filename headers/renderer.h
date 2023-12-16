#ifndef CWS_RENDERER_H
#define CWS_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"
#include "mesh.h"
#include "model.h"

namespace cws::graphics {

	class Renderer {
		public:
			Renderer();
			void clear(glm::vec4 clear_color, GLbitfield mask);

			void render(const renderdata::Mesh& mesh);
			void render(ShaderProgram& program, const renderdata::RawModel& model);
	};

};

#endif