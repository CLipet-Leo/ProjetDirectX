#pragma once

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);

	void GetInput(int *_pParam);
	void EnableController();
	void DisableController();

private:
	bool _bAbleController;
};