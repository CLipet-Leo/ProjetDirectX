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
	if (_bActiveController)
	{
		switch (pParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VKm_Z:
			OutputDebugStringA("Z KeyDown \n");
			_pMoveComp->UpdateDirectorVect({ 10.f * gt.getDeltaTime() ,0.f, 0.f });
			//_pMoveComp->UpdateRotation({ XMConvertToRadians(45.0f), 0.0f, 0.0f });
			//_pMoveComp->UpdateTransform();
			break;
		case VKm_Q:
			OutputDebugStringA("Q KeyDown \n");
			_pMoveComp->UpdateDirectorVect({0.f ,0.f, -10.f * gt.getDeltaTime() });
			break;
		case VKm_S:
			OutputDebugStringA("S KeyDown \n");
			_pMoveComp->UpdateDirectorVect({ -10.f * gt.getDeltaTime() ,0.f, 0.f });
			break;
		case VKm_D:
			OutputDebugStringA("D KeyDown \n");
			_pMoveComp->UpdateDirectorVect({ 0.f ,0.f, 10.f * gt.getDeltaTime() });
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