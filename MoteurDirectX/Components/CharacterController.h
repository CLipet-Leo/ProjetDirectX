#pragma once

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params, Component* pMoveComp);

	void GetInput(WPARAM pParam);
	void EnableController();
	void DisableController();

	void Update(const Timer& gt) override;

private:
	bool _bAbleController;

	Component* _pMoveComp;
};