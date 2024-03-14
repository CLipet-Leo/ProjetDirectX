#pragma once

class GameObject : public Component
{
public:
	GameObject(Entity* _pEOwner, Params* params);
	void InitComponent(ID3D12Device* d3dDevice) override;

	void takeDamage(int iDamage);
	int getDamage();

private:
	int _iHealth;
	int _iDamage;
	Params* _Params;
};
