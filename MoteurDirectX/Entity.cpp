// Include needed classes
#include "includes/Pch.h"
#include "includes/Entity.h"

#include <windows.h>
#include <stdio.h>
#define VSCPrint(buffer, msg, ...) \
    do{ \
        _snprintf_s(buffer, sizeof(buffer), _TRUNCATE, msg, __VA_ARGS__); \
        OutputDebugStringA(buffer); \
    } while(0)
char buff[200]; // Global within the class (in main.cpp, it's a member to avoid problems)


// Constru & Destru
Entity::Entity()
{
	// Creates and reset a Transform object, and gives it to the Entity
	Transform* TEntityTransform = new Transform();
	TEntityTransform->Identity();
	_pTransform = TEntityTransform;

	// Initalize Component List with an empty vecotr. Not doing this makes compiler go no no :3
	_LpComponents = std::vector<Component*>();

	//_LpEntity.push_back(this);
}
Entity::~Entity()
{
	// Destroys the Entity's Transform object
	delete _pTransform;

	// Destroys every single Component linked to the Entity
	for (auto curPComp : _LpComponents)
	{
		RmvComponent(curPComp->GetCompSubType());
	}

	//for (auto curPEntity : _LpEntity)
	//{
	//	int iterator = 0;
	//	// If it's found, destroys & removes it
	//	if (curPEntity == this)
	//	{
	//		_LpEntity.erase(_LpEntity.begin() + iterator);
	//	}
	//	iterator++;
	//}

	std::cout << "ENTITY : Destructor called !\n";
}

// Add a Component to the Entity. This doesn't work if it already has it
void Entity::AddComponent(Component* ARGpComp)
{
	// Checks is the Component isn't already present
	for (auto pComp : _LpComponents)
	{
		// If it's already in there, quits the function
		if (pComp->GetCompSubType() == ARGpComp->GetCompSubType())
		{
			std::cout << "Component is already there !\n";
			return;
		}
	}

	// Adds the Component if it's already there
	_LpComponents.push_back(ARGpComp);
}

// Remove a Component of the Entity. This doesn't work if it doesn't already have it
void Entity::RmvComponent(compSubType ARGCompTypeTarget)
{
	// Look for a Component of this type
	int iterator = 0;
	for (auto pComp : _LpComponents)
	{
		// If it's found, destroys & removes it
		if(pComp->GetCompSubType() == ARGCompTypeTarget)
		{
			delete _LpComponents.at(iterator);
			_LpComponents.erase(_LpComponents.begin() + iterator);
			return;
		}
		iterator++;
	}
}

void Entity::UpdateComponents(const Timer& gt)
{
	for (auto curComponent : _LpComponents)
	{
		curComponent->Update(gt);
	}
}

Component* Entity::GetComponentPtr(compSubType ARGCompTypeTarget)
{
	for (auto curComponent : _LpComponents)
	{
		if (curComponent == nullptr)
			continue;

		if (curComponent->GetCompSubType() == ARGCompTypeTarget)
			return curComponent;
	}
	return nullptr;
}

Transform* Entity::GetTransformPtr()
{
	return _pTransform;
}

void Entity::UpdateTransform(XMFLOAT3* f3VectorDirector)
{

	_pTransform->mPos._41 = f3VectorDirector->x;
	_pTransform->mPos._42 = f3VectorDirector->y;
	_pTransform->mPos._43 = f3VectorDirector->z;

	VSCPrint(buff, "dirVect: x: %f, y: %f, z: %f\n", f3VectorDirector->x, f3VectorDirector->y, f3VectorDirector->z);

	_pTransform->UpdateMatrix();

	VSCPrint(buff, "matrix: x: %f, x2: %f, x3: %f, x4: %f\nmatrix: y: %f, y2: %f, y3: %f, y4: %f\nmatrix: z: %f, z2: %f, z3: %f, z4: %f\n",
		_pTransform->matrix._11, _pTransform->matrix._12, _pTransform->matrix._13,
		_pTransform->matrix._21, _pTransform->matrix._22, _pTransform->matrix._23,
		_pTransform->matrix._31, _pTransform->matrix._32, _pTransform->matrix._33,
		_pTransform->matrix._41, _pTransform->matrix._42, _pTransform->matrix._43);

}

std::vector<Component*>* Entity::GetPCompListPtr()
{
	return &_LpComponents;
}