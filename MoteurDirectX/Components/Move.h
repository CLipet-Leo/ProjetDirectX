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
	Move(Entity* pEOwner, Params* params);
	~Move();

	// Methods
	void Update(const Timer& gt)override;
	void UpdateTransform();
	XMFLOAT3 GetVectorDirector();
};