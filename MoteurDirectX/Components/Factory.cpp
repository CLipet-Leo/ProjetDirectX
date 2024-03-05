#include "../includes/Pch.h"
#include "Factory.h"
#include <typeinfo>

using namespace DirectX;

Factory::Factory(Entity* pEOwner, int* iCallback=0)
	: Component(pEOwner, FACTORY)
{
	// Copy the Components' pointers
	std::vector<Component*>* pCompListPtr = pEOwner->GetPCompListPtr();
	for (auto pCompList : *pCompListPtr)
	{
		if (pCompList->GetCompSubType() == FACTORY)
		{
			continue;
		}
		// add cur comp to the copy list
		_pCompCopyList.push_back(pCompList);
	}
}

void Factory::CreateEntity()
{
	// TODO
	// instanciate Entity.
	Entity* newEntity = new Entity();
	Component* curNewComp;
	for (auto curPComponent : _pCompCopyList)
	{
		switch (curPComponent->GetCompSubType())
		{
		case MOVE:
			curNewComp = new Move(_pEOwner, curPComponent->GetVectorDirector(), 5.f);
			break;
		case COLLIDER:
			//curNewComp = new Factory(_pEOwner);
			break;
		case ROTATE:
			//curNewComp = new Factory(_pEOwner);
			break;
		case GAME_OBJECT:
			curNewComp = new GameObject(_pEOwner);
			break;
		}
		newEntity->AddComponent(curNewComp);

		//delete curNewComp;
	}

	delete newEntity;
	delete curNewComp;

	// use Entity::AddComponent() to add every copied components.
}