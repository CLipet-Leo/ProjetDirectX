#pragma once
class GameObject
{
public:

	GameObject(int iDamage, int iHealth);

	void takeDamage(int iDamage);
	int getDamage();

private:
	int _iHealth;
	int _iDamage;
};
