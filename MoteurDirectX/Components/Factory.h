#pragma once
#include "../includes/Component.h"

class Factory: public Component
{
public:

	Factory(Entity* pEOwner, int* iCallback);

	void CreateEntity();

private:
	std::vector<Component*> _pCompCopyList;


};
