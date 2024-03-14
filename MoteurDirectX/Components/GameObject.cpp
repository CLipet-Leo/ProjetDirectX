#include "../includes/Pch.h"

GameObject::GameObject(Entity* _pEOwner, Params* params)
	: Component(_pEOwner, GAME_OBJECT), _Params(params)
{

}

void GameObject::InitComponent(ID3D12Device* d3dDevice)
{
	_iDamage = _Params->gameObjectParams.iDamage;
	_iHealth = _Params->gameObjectParams.iHealth;
}

void GameObject::takeDamage(int iDamage)
{
	_iHealth -= iDamage;
}

int GameObject::getDamage()
{
	return _iDamage;
}