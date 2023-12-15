#ifndef CWS_RENDERER_H
#define CWS_RENDERER_H

#include <glm/glm.hpp>
#include "mesh.h"

namespace cws::graphics {

	class Renderer {
		public:
			Renderer();
			void clear(glm::vec4 clear_color, GLbitfield mask);

			void render(const data::Mesh& mesh);
	};

};

#endif