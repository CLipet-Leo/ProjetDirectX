// Include needed classes
#include "./Component.h"

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