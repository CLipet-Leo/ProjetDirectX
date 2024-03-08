#pragma once

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);

	void GetInput(WPARAM pParam);
	void EnableController();
	void DisableController();

private:
	bool _bAbleController;
};