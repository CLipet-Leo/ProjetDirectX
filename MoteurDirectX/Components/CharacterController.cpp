#include "../includes/Pch.h"

CharacterController::CharacterController(Entity* _pEOwner, Params* params)
	: Component(_pEOwner, GAME_OBJECT), _bAbleController(false)
{

}

void CharacterController::GetInput(int *_pParam)
{
	if (_bAbleController && WM_KEYDOWN)
	{
		switch (*_pParam)
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


void CharacterController::EnableController()
{
	_bAbleController = true;
}

void CharacterController::DisableController()
{
	_bAbleController = false;
}