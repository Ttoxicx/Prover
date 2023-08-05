#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <glm/glm.hpp>
class Object {
public:
	void setLocation(const glm::vec3& location) { _location = location; }
	glm::vec3 getLocation() { return _location; }
	void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
	glm::vec3 getRotation() { return _rotation; }
public:
	virtual void tick(float deltatime) {};
public:
	bool tickEnabled = true;
	bool moveable = false;
private:
	glm::vec3 _location = glm::vec3(0.f);
	glm::vec3 _rotation = glm::vec3(0.f);
};
#endif // !_OBJECT_H_
