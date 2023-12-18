#ifndef CWS_RENDERER_H
#define CWS_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/shaderprogram.h"
#include "models/models.h"

namespace cws::graphics {

	class Renderer {
		public:
			Renderer();
			void clear(glm::vec4 clear_color, GLbitfield mask);

			void render(const models::Mesh& mesh);
			void render(ShaderProgram& program, const models::RawModel& model);
			void render(ShaderProgram& program, const models::TexturedModel& model);
	};

};

#endif