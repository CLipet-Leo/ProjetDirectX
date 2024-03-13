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
	std::vector<Component*> _LpComponents;

public:
	// Constru & Destru
	Entity();
	~Entity();

	// Methods to manage components
	void AddComponent(Component* ARGpComp);
	void RmvComponent(compSubType ARGCompTypeTarget);

	// Methods to change the Entity's state and data
	void UpdateComponents(const Timer& gt);
	void UpdateTransform(XMFLOAT3* f3VectorDirector);

	// Getter & Setter
	Transform* GetTransformPtr();
	std::vector<Component*>* GetPCompListPtr();
	Component* GetComponentPtr(compSubType ARGCompTypeTarget);
};