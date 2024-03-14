#pragma once

class GameObject : public Component
{
public:
	GameObject(Entity* _pEOwner, Params* params);
	void InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality) override;

	void takeDamage(int iDamage);
	int getDamage();

private:
	int _iHealth;
	int _iDamage;
	Params* _Params;
};
