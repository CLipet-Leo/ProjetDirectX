// Include needed classes
#include "includes/Pch.h"
#include "includes/Component.h"

// Include C++ standard libs
#include <iostream>

// Constru & Destru
Component::Component(Entity* pEArgOwner, compSubType subType=UNKNOWN)
	:_pEOwner(pEArgOwner), _compSubType(subType)
{

}
Component::~Component()
{
	std::cout << "COMPONENT : Destructor called !\n";
}

// Getter & Setter
compSubType Component::GetCompSubType()
{
	return this->_compSubType;
}

XMFLOAT3 Component::GetVectorDirector()
{
	return {};
}

void Component::Update(const Timer& gt)
{

}

void Component::InitComponent()
{
	
}
