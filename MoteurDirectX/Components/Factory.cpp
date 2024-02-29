#include "Factory.h"
#include "../Entity.h"
#include <typeinfo>

Factory::Factory(Entity* pEOwner, int* iCallback=0)
	: Component(pEOwner)
{
	std::vector<Component*>* pCompListPtr = pEOwner->GetPCompListPtr();
	for (auto pCompList : *pCompListPtr)
	{
		if (typeid(pCompList) == typeid(Factory))
		{
			*iCallback = 1;
		}
	}
}