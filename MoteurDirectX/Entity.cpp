// Include C++ standard tools
#include <iostream>

// Include needed classes
#include "./Entity.h"
#include "./Component.h"


// Constru & Destru
Entity::Entity()
{
	//Call Transform constru with IdMatrix as TRS
}
Entity::~Entity()
{
	// Emtpy lmao
}

// Add a Component to the Entity. This doesn't work if it already has it
void Entity::AddComponent(Component* ARGpComp)
{
	// Checks is the Component isn't already present
	for (auto pComp : _pCompList)
	{
		// If it's already in there, quits the function
		if (pComp->GetCompSubType() == ARGpComp->GetCompSubType())
		{
			std::cout << "Component is already there !\n";
			return;
		}
	}

	// Adds the Component if it's already there
	_pCompList.push_back(ARGpComp);
}

// Remove a Component of the Entity. This doesn't work if it doesn't already have it
void Entity::RmvComponent(compSubType ARGCompTypeTarget)
{
	// Look for a Component of this type
	int iterator = 0;
	for (auto pComp : _pCompList)
	{
		// If it's found, removes it and calls the destructor on Component (this destroys the parent and the child)
		if (pComp->GetCompSubType() == ARGCompTypeTarget)
		{
			_pCompList.at(iterator)->~Component();
			_pCompList.erase(_pCompList.begin() + iterator);
			return;
		}
		iterator++;
	}
}

std::vector<Component*>* Entity::GetPCompListPtr()
{
	return &_pCompList;
}