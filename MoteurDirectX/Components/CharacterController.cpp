#include "../includes/Pch.h"
#include "../Components/Move.h"
#include "../Components/Camera.h"

CharacterController::CharacterController(Entity* _pEOwner, Params* params)
	: Component(_pEOwner, CHARACTER_CONTROLLER)
{

}

void CharacterController::InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality)
{
	_bActiveController = true;
	_pMoveComp = (Move*)_pEOwner->GetComponentPtr(MOVE);
	_pCameraComp = (Camera*)_pEOwner->GetComponentPtr(CAMERA);
}

void CharacterController::GetInput(WPARAM pParam)
{
	
}

void CharacterController::Update(const Timer& gt, WPARAM pParam)
{
	if (_bActiveController && WM_KEYDOWN)
	{
		switch (pParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VKm_Z:
			OutputDebugStringA("Z KeyDown \n");
			_pCameraComp->UpdateCam(0, -5);
			break;
		case VKm_Q:
			OutputDebugStringA("Q KeyDown \n");
			_pCameraComp->UpdateCam(-5, 0);
			break;
		case VKm_S:
			OutputDebugStringA("S KeyDown \n");
			_pCameraComp->UpdateCam(0, +5);
			break;
		case VKm_D:
			OutputDebugStringA("D KeyDown \n");
			_pCameraComp->UpdateCam(+5, 0);
			break;
		case VKm_E:
			OutputDebugStringA("E KeyDown \n");
			break;
		case VK_SPACE:
			OutputDebugStringA("SPACE KeyDown \n");
			break;
		}
	}
}

void CharacterController::EnableController()
{
	_bActiveController = true;
}

void CharacterController::DisableController()
{
	_bActiveController = false;
}