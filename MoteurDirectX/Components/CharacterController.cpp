#include "../includes/Pch.h"

CharacterController::CharacterController(Entity* _pEOwner, Params* params, Component* pMoveComp)
	: Component(_pEOwner, GAME_OBJECT), _bAbleController(true), _pMoveComp(pMoveComp)
{

}

void CharacterController::GetInput(WPARAM pParam)
{
	if (_bAbleController && WM_KEYDOWN)
	{
		switch (pParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		//case VK_F2:
		//	Set4xMsaaState(!b4xMsaaState);
		//	break;
		case VKm_Z:
			OutputDebugStringA("Z KeyDown \n");
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

void CharacterController::Update(const Timer& gt)
{

}

void CharacterController::EnableController()
{
	_bAbleController = true;
}

void CharacterController::DisableController()
{
	_bAbleController = false;
}