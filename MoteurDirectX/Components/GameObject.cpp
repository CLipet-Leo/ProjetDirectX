#include "../includes/Pch.h"

GameObject::GameObject(Entity* _pEOwner, Params* params)
	: Component(_pEOwner, GAME_OBJECT), _iDamage(params->gameObjectParams.iDamage), _iHealth(params->gameObjectParams.iHealth)
{

}

void GameObject::takeDamage(int iDamage)
{
	_iHealth -= iDamage;
}

int GameObject::getDamage()
{
	return _iDamage;
}