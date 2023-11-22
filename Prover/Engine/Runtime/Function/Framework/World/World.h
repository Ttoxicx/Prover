#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Object;

class World {
public:
	World();
	~World();
	template<typename T> const std::shared_ptr<T> spawnObject(const glm::vec3& loc = glm::vec3(0));

public:
	virtual void tick(float deltaTime);
private:
	std::vector<std::shared_ptr<Object>> _objectList;
};

#endif // !_WORLD_H_
