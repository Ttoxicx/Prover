#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_
#include <Basic/Component.h>
#include "Basic/Camera.h"
#include <glm/glm.hpp>
class CameraComponent :public Component {
public:
	void setCameraLag(float lagtime) {}//TODO(����ӳٸ���)
public:
	virtual void tickComponent() override;
public:
	Camera _camera;
};
#endif // !_CAMERACOMPONENT_H_
