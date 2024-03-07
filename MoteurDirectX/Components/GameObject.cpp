#include "../includes/Pch.h"

GameObject::GameObject(Entity* _pEOwner, GameObjectParams* params)
	: Component(_pEOwner, GAME_OBJECT), _iDamage(params->iDamage), _iHealth(params->iHealth)
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