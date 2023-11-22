#include "Framework/World/World.h"
#include "Framework/Object/Object.h"

World::World() 
{

}

World::~World() 
{

}

template<typename T> const std::shared_ptr<T> World::spawnObject(const glm::vec3& loc) 
{
	
}

void World::tick(float deltaTime) 
{
	for (auto obj : _objectList) {
		if (obj->tickEnabled) {
			obj->tick(deltaTime);
		}
	}
}
