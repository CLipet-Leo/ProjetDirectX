#pragma once

// Forward include
class Move;
class Camera;

class CharacterController : public Component
{
public:
	CharacterController(Entity* _pEOwner, Params* params);
	void InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality) override;

	void GetInput(WPARAM pParam);
	void EnableController();
	void DisableController();

	void Update(const Timer& gt, WPARAM pParam);

private:
	bool _bActiveController;

	Component* _pMoveComp;
	Camera* _pCameraComp;
};