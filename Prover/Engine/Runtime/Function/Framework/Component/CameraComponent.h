#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_
#include "Framework/Component/Component.h"
#include "Render/Camera/Camera.h"
#include <glm/glm.hpp>
class CameraComponent :public Component {
public:
	void setCameraLag(float lagtime) {}//TODO(����ӳٸ���)
public:
	virtual void tickComponent(double deltaTime) override;
public:
	Camera _camera;
};
#endif // !_CAMERACOMPONENT_H_
