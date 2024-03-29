#pragma once

using namespace DirectX;

// Forward declarations

class Move : public Component
{
private:
	XMFLOAT3 _v3VectorDirector;
	float _fVelocity;
	Params* _Params;

public:
	// Constru & Destru
	Move(Entity* pEOwner, Params* params);
	void InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality) override;
	~Move();

	// Methods
	void Update(const Timer& gt)override;
	void UpdateTransform();
	XMFLOAT3 GetVectorDirector();
};