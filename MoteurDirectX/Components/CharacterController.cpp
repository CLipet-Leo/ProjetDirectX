#include "../includes/Pch.h"

CharacterController::CharacterController(Entity* _pEOwner, Params* params)
	: Component(_pEOwner, CHARACTER_CONTROLLER), _bActiveController(true), _pMoveComp((Move*)_pEOwner->GetComponentPtr(MOVE))//, _pCameraComp(_pEOwner->GetComponentPtr(CAMERA))
{

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
			_pMoveComp->UpdateDirectorVect({1 * gt.getDeltaTime() ,0,0});
			_pMoveComp->UpdateTransform();
			break;
		case VKm_Q:
			OutputDebugStringA("Q KeyDown \n");
			break;
		case VKm_S:
			OutputDebugStringA("S KeyDown \n");
			break;
		case VKm_D:
			OutputDebugStringA("D KeyDown \n");
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