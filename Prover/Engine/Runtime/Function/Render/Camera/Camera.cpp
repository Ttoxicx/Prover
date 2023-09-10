#include "Render/Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::updateCameraInfo()
{
	if (_projectionMode == ProjectionMode::Perspective) {
		_projectionMatrix = glm::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);
	}
	else {
		_projectionMatrix = glm::ortho(0.f, _width, 0.f, _height, _nearPlane, _farPlane);
	}
	_frontVector.x = glm::cos(glm::radians(_rotation.x)) * glm::cos(glm::radians(_rotation.y));
	_frontVector.y = glm::sin(glm::radians(_rotation.x));
	_frontVector.z = glm::cos(glm::radians(_rotation.x)) * glm::sin(glm::radians(_rotation.y));
	_frontVector = glm::normalize(_frontVector);
	_rightVector = glm::normalize(glm::cross(_frontVector, _upVector));
	_viewMatrix = glm::lookAt(_location, _location + _frontVector, _upVector);
}