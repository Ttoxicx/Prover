#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <memory>

class World;

class Level {
public:
	Level();
	~Level();

public:
	virtual void tick(float deltaTime);
private:
	std::shared_ptr<World> _currentWorld = nullptr;
	std::vector<std::shared_ptr<World>> _objectList;
};

#endif // !_LEVEL_H_
