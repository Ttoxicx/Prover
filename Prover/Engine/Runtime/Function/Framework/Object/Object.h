#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Component;

class Object {
public:
	inline void setLocation(const glm::vec3& location) { _location = location; }
	inline glm::vec3 getLocation() { return _location; }
	inline void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
	inline glm::vec3 getRotation() { return _rotation; }
	void addComponent(std::shared_ptr<Component> component);
	void removeComponent(std::shared_ptr<Component> component);
	void clearComponent();
	template<typename T> 
	const std::shared_ptr<T> getComponent(){
		for (auto value : _componentList) {
			std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(value);
			if (result != nullptr) {
				return result;
			}
		}
		return nullptr;
	}
public:
	virtual void tick(float deltatime);
public:
	bool tickEnabled = true;
	bool moveable = false;
private:
	glm::vec3 _location = glm::vec3(0.f);
	glm::vec3 _rotation = glm::vec3(0.f);
private:
	std::vector<std::shared_ptr<Component>> _componentList;
};
#endif // !_OBJECT_H_
