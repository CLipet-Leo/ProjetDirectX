#pragma once
#include "../Component.h"
#include <vector>

class Factory: public Component
{
public:

	Factory(Entity* pEOwner, int* iCallback);

	void CreateEntity();

private:
	std::vector<Component*> _pCompCopyList;


};
