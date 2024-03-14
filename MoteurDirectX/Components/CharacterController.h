#pragma once

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);
	void InitComponent(ID3D12Device* d3dDevice) override;

	void GetInput(WPARAM pParam);
	void EnableController();
	void DisableController();

	void Update(const Timer& gt, WPARAM pParam);

private:
	bool _bActiveController;

	Component* _pMoveComp;
	Component* _pCameraComp;
};