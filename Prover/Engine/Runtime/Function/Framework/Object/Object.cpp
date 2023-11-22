#include "Framework/Object/Object.h"
#include "Framework/Component/Component.h"

void Object::addComponent(std::shared_ptr<Component> component)
{
	for (auto value : _componentList) {
		if (value == component) {
			throw "this component has already existed in this object";
		}
	}
	_componentList.push_back(component);
}
void Object::removeComponent(std::shared_ptr<Component> component)
{
	std::vector<std::shared_ptr<Component>>::iterator componentToRemove = _componentList.end();
	auto itr = _componentList.begin();
	for (itr; itr != _componentList.end(); ++itr) {
		if ((*itr) == component) {
			componentToRemove = itr;
			break;
		}
	}
	if (componentToRemove != _componentList.end()) {
		_componentList.erase(componentToRemove);
	}
}
void Object::clearComponent()
{
	_componentList.clear();
}
template<typename T> const std::shared_ptr<T> Object::getComponent()
{
	for (auto value : _componentList) {
		std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(value);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}
void Object::tick(float deltatime)
{
	for (auto value : _componentList) {
		if (value->tickComponentEnabled) {
			value->tickComponent(deltatime);
		}
	}
}