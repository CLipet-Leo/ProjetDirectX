#include "./Component.h"

// Constru & Destru
Component::Component(Entity* pEArgOwner)
{
	this->_pEOwner = pEArgOwner;
	this->_compSubType = UNKNOWN;
}
Component::~Component()
{
	// Empty lol
}

// Getter & Setter
compSubType Component::GetCompSubType()
{
	return this->_compSubType;
}