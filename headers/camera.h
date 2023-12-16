#ifndef CWS_CAMERA_H
#define CWS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cws::world {

	class Camera {
		public:
			glm::vec3 position;

			Camera(
				glm::vec3 position,
				float fov = 45.0f,
				float aspect = 16.0f / 9.0f,
				float near = 0.1f,
				float far = 100.0f
			);

			void update(float x, float y);

			const glm::mat4& get_view_matrix();
			const glm::mat4& get_projection_matrix() const;
			const glm::vec3& get_front_vector() const;
			const glm::vec3& get_right_vector() const;

			void set_fov(float fov);
			void set_aspect(float aspect);
			void set_view_distance(float near, float far);
		private:
			void update_projection_matrix();

			float m_fov, m_aspect_ratio, m_near, m_far;

			glm::mat4 m_projection_mat;
			glm::mat4 m_view_mat;

			glm::vec3 m_up_vector;
			glm::vec3 m_front_vector;
			glm::vec3 m_right_vector;

			float m_yaw;
			float m_pitch;

			float m_last_x;
			float m_last_y;

			bool m_first_move;
	};

};

#endif