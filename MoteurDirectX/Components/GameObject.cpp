#include "../includes/Pch.h"

GameObject::GameObject(Entity* _pEOwner, int iDamage = 0, int iHealth = 1)
	: Component(_pEOwner, GAME_OBJECT), _iDamage(iDamage), _iHealth(iHealth)
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