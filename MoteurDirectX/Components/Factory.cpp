#include "../includes/Pch.h"
#include "Factory.h"

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


}