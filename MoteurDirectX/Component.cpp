// Include needed classes
#include "./Component.h"

// Include C++ standard libs
#include <iostream>

// Constru & Destru
Component::Component(Entity* pEArgOwner)
{
	this->_pEOwner = pEArgOwner;
	this->_compSubType = UNKNOWN;
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