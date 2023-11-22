#include "Framework/Level/Level.h"
#include "Framework/World/World.h"

Level::Level()
{

}

Level::~Level()
{

}

void Level::tick(float deltaTime) 
{
	if (_currentWorld != nullptr) {
		_currentWorld->tick(deltaTime);
	}
}