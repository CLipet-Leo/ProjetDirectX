#pragma once

// Forward declarations

class Move : public Component
{
private:
	XMFLOAT3 _v3VectorDirector;
	float _fVelocity;

public:
	// Constru & Destru
	Move(Entity* pEOwner, float ARGfVelocity, XMFLOAT3 ARGv3VectorDirector);
	~Move();

	// Methods
	void UpdateTransform();
	XMFLOAT3 GetVectorDirector();
};