#pragma once

using namespace DirectX;

// Forward declarations

class Move : public Component
{
private:
	XMFLOAT3 _v3VectorDirector;
	float _fVelocity;

public:
	// Constru & Destru
	Move(Entity* pEOwner, XMFLOAT3 ARGv3VectorDirector, float ARGfVelocity = 5.f);
	~Move();

	// Methods
	void Update(const Timer& gt)override;
	void UpdateTransform();
	XMFLOAT3 GetVectorDirector();
};