#include "world/camera.h"

using namespace cws::world;

Camera::Camera(
	glm::vec3 position,
	float fov,
	float aspect,
	float near,
	float far
) :
	position(position),
	m_fov(fov),
	m_aspect_ratio(aspect),
	m_near(near),
	m_far(far),
	m_yaw(-90.0f),
	m_pitch(0.0f),
	m_last_x(0.0f),
	m_last_y(0.0f),
	m_first_move(true)
{
	m_up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_front_vector = glm::vec3(0.0f, 0.0f, 1.0f);
	update_projection_matrix();
}

void Camera::update(float x, float y) {
	if (m_first_move) {
		m_last_x = x;
		m_last_y = y;
		m_first_move = false;
		return;
	}

	float offset_x = x - m_last_x;
	float offset_y = m_last_y - y; // reversed since y goes from bottom to top
	
	m_last_x = x;
	m_last_y = y;

	float sens = 0.1f;
	offset_x *= sens;
	offset_y *= sens;

	m_yaw += offset_x;
	m_pitch += offset_y;

	if (m_pitch > 89.0f) {
		m_pitch = 89.0f;
	} else if (m_pitch < -89.0f) {
		m_pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front_vector = glm::normalize(direction);
	m_right_vector = glm::normalize(glm::cross(m_front_vector, m_up_vector));
}

void Camera::set_fov(float fov) {
	m_fov = fov;

	update_projection_matrix();
}

void Camera::set_aspect(float aspect) {
	m_aspect_ratio = aspect;

	update_projection_matrix();
}

void Camera::set_view_distance(float near, float far) {
	m_near = near;
	m_far = far;

	update_projection_matrix();
}

void Camera::update_projection_matrix() {
	m_projection_mat = glm::perspective(
		glm::radians(m_fov),
		m_aspect_ratio,
		m_near,
		m_far
	);
}

const glm::mat4& Camera::get_view_matrix() {
	m_view_mat = glm::lookAt(
		position,
		position + m_front_vector,
		m_up_vector
	);
	
	return m_view_mat; 
}

const glm::mat4& Camera::get_projection_matrix() const {
	return m_projection_mat;
}

const glm::vec3& Camera::get_front_vector() const {
	return m_front_vector;
}

const glm::vec3& Camera::get_right_vector() const {
	return m_right_vector;
}

float Camera::get_fov() const {
	return m_fov;
}

float Camera::get_aspect() const {
	return m_aspect_ratio;
}

float Camera::get_near() const {
	return m_near;
}

float Camera::get_far() const {
	return m_far;
}

void Camera::set_last_mouse_pos(float x, float y) {
	m_last_x = x;
	m_last_y = y;
}