#include "../includes/Pch.h"

GameObject::GameObject(Entity* _pEOwner, int iDamage, int iHealth)
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