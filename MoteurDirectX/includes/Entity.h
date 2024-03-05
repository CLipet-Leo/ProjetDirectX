#pragma once
#include "Component.h"

// Forward delcarations
class Transform;
class Component;

// Entity class (basically our GameObjects)
// Adds components since it can't do anything on its own
class Entity
{
private:
	Transform* _pTransform;
	static std::vector<Component*> _LpComponents;
	static std::vector<Entity*> _LpEntity;

public:
	// Constru & Destru
	Entity();
	~Entity();

	// Methods to manage components
	void AddComponent(Component* ARGpComp);
	void RmvComponent(compSubType ARGCompTypeTarget);

	std::vector<Component*>* GetPCompListPtr();
};