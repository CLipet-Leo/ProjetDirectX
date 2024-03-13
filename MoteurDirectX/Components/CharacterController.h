#pragma once
#include "Move.h"

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);

	void EnableController();
	void DisableController();

	void Update(const Timer& gt, WPARAM pParam);

private:
	bool _bActiveController;

	Move* _pMoveComp;
	//Component* _pCameraComp;
};