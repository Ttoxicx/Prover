#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "Basic/Object.h"
#include <glm/glm.hpp>
class Component {
public:
	virtual void tickComponent() {};
public:
	void attachToObject(Object* object) { _object = object; }
	void distachFromObject(Object* object) { _object = nullptr; }
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
	Object* _object = nullptr;
	glm::vec3 _relativeLocation = glm::vec3(0.f);
	glm::vec3 _relativeRotation = glm::vec3(0.f);
	glm::vec3 _worldLocation = glm::vec3(0.f);
	glm::vec3 _worldRotation = glm::vec3(0.f);
};
#endif // !_COMPONENT_H_
