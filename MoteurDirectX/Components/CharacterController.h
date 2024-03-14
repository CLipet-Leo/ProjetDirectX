#pragma once

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);
	void InitComponent() override;

	void GetInput(WPARAM pParam);
	void EnableController();
	void DisableController();

	void Update(const Timer& gt, WPARAM pParam);

private:
	bool _bActiveController;

	Component* _pMoveComp;
	Component* _pCameraComp;
};