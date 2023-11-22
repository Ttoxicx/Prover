#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "Framework/Object/Object.h"
#include <glm/glm.hpp>
#include <memory>

class Component {
public:
	virtual void tickComponent(double deltaTime) {};
public:
	void attachToObject(std::shared_ptr<Object> object) { _object = object; }
	void distachFromObject(std::shared_ptr<Object> object) { _object.reset(); }
public:
	inline void setRelativeLocation(const glm::vec3& relativelocation) { _relativeLocation = relativelocation; }
	inline void setRelativeRotation(const glm::vec3& relativeRotation) { _relativeRotation = relativeRotation; }
	inline void setWorldLocation(const glm::vec3& worldLocation) { _worldLocation = worldLocation; }
	inline void setWorldRotation(const glm::vec3& worldRotation) { _worldRotation = worldRotation; }
	inline glm::vec3 getRelativeLocation() { return _relativeLocation; }
	inline glm::vec3 getRelativeRotation() { return _relativeRotation; }
	inline glm::vec3 getWorldLocation() { return _worldLocation; }
	inline glm::vec3 getWorldRotation() { return _worldRotation; }
public:
	bool tickComponentEnabled = false;
protected:
	std::shared_ptr<Object> _object;
	glm::vec3 _relativeLocation = glm::vec3(0.f);
	glm::vec3 _relativeRotation = glm::vec3(0.f);
	glm::vec3 _worldLocation = glm::vec3(0.f);
	glm::vec3 _worldRotation = glm::vec3(0.f);
};
#endif // !_COMPONENT_H_
