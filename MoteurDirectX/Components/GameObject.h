#pragma once

class GameObject : public Component
{
public:
	GameObject(Entity* _pEOwner, Params* params);

	void takeDamage(int iDamage);
	int getDamage();

private:
	int _iHealth;
	int _iDamage;
};
