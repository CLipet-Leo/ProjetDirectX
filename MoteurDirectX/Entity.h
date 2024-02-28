#pragma once

// Includes (std::vector can't be forward declared UnU)
#include <vector>

// Forward delcarations
class Transform;
class Component;

// Entity class (basically our GameObjects)
// Adds components since it can't do anything on its own
class Entity
{
private:
	Transform* _pTransform;
	std::vector<Component*> _pCompList;

public:
	// Constru & Destru
	Entity::Entity();
	Entity::~Entity();

	// Methods to manage components
	void Entity::AddComponent(Component* ARGpComp);
	void Entity::RmvComponent(compSubType ARGCompTypeTarget);
};