#include "Factory.h"
#include "GameObject.h"
#include "Move.h"
//#include "Collider.h"
//#include "Rotate.h"
#include "../Entity.h"
#include <typeinfo>

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
	for (auto curPComponent : _pCompCopyList)
	{
		Component* curNewComp;
		switch (curPComponent->GetCompSubType())
		{
		case MOVE:
			curNewComp = new Move(_pEOwner, curPComponent->GetVectorDirector());
			break;
		case COLLIDER:
			//curNewComp = new Factory(_pEOwner);
			break;
		case ROTATE:
			//curNewComp = new Factory(_pEOwner);
			break;
		case GAME_OBJECT:
			curNewComp = new Factory(_pEOwner);
			break;
		}
		newEntity->AddComponent(curPComponent);

		delete curNewComp;
	}
	// use Entity::AddComponent() to add every copied components.
}