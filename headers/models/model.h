#ifndef CWS_MODEL_H
#define CWS_MODEL_H

#include "models/mesh.h"
#include "graphics/texture.h"

#include <vector>

namespace cws::models {

	struct Transform {
		glm::vec3 position = glm::vec3();
		glm::vec3 rotation = glm::vec3();
		glm::vec3 scale = glm::vec3(1.0f);
	};

	class RawModel {
		public:
			RawModel() {}

			RawModel(
				const std::vector<Mesh>& meshes,
				const Transform& transform = {}
			);

			RawModel(
				const Mesh& mesh,
				const Transform& transform = {}
			);

			void add_mesh(const Mesh& mesh);

			// getters
			const std::vector<Mesh>& get_meshes() const;

			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

		private:
			std::vector<Mesh> m_meshes;
	};

	class TexturedModel {
		public:
			TexturedModel() {}

			TexturedModel(
				const cws::graphics::Texture& texture,
				const RawModel& raw_model
			);

			const cws::graphics::Texture& get_texture() const;
			const RawModel& get_raw_model() const;

		private:
			cws::graphics::Texture m_texture;
			RawModel m_model;
	};

};

#endif