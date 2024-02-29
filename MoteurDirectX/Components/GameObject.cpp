#include "GameObject.h"

GameObject::GameObject(int iDamage=0, int iHealth=1)
	:_iDamage(iDamage), _iHealth(iHealth)
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