#pragma once

class GameObject : public Component
{
public:

	GameObject(Entity* _pEOwner, int iDamage = 0, int iHealth = 1);

	void takeDamage(int iDamage);
	int getDamage();

private:
	int _iHealth;
	int _iDamage;
};
