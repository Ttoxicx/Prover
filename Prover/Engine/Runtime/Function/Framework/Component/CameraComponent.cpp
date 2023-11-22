#include "Framework/Component/CameraComponent.h"
void CameraComponent::tickComponent(double deltaTime) {
	if (_object != nullptr) {
		_camera.setCameraLocation(_object->getLocation() + _relativeLocation);
		_camera.setCameraRotation(_object->getRotation() + _relativeRotation);
	}
}