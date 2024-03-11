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
	std::vector<Component*> _LpComponents;
	//Component* _v3VectorDirector;
	Transform* _pTransform;

public:
	// Constru & Destru
	Entity();
	~Entity();

	// Methods to manage components
	void AddComponent(Component* ARGpComp);
	void RmvComponent(compSubType ARGCompTypeTarget);
	void UpdateComponents(const Timer& gt);
	Component* GetComponentPtr(compSubType ARGCompTypeTarget);
	void UpdateTransform(XMFLOAT3* f3VectorDirector, XMFLOAT3* f3Rotation);
	Transform* GetTransformPtr();

	std::vector<Component*>* GetPCompListPtr();
};