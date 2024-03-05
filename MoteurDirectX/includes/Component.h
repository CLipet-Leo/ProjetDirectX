#pragma once
#include "Entity.h"
// Forward declarations
//class Entity;

// Enum for Component to keep track of its sub-class
// TODO : Move that in a general purpose header ? Maybe not since Entity, and Component sub-classes import this Component.h

// Component class.
// Bridge between component sub-classes (if they need to interact), and interface for Entity to "attach" them
class Component
{
protected:
	Entity* _pEOwner;
	compSubType _compSubType;

public:
	// Constru & Destru
	Component::Component(Entity* pEArgOwner, compSubType subType);
	virtual Component::~Component();

	// Getter & Setter
	compSubType Component::GetCompSubType();
	virtual XMFLOAT3 Component::GetVectorDirector();

	// Unsure if this is needed, we'll see by implementing actual Components sub-classes
	// Would be called every frame, and do stuff
	void Component::Update();
};