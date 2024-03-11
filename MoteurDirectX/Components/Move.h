#pragma once

using namespace DirectX;

// Forward declarations

class Move : public Component
{
private:
	XMFLOAT3 _v3VectorDirector;
	XMFLOAT3 _pTransform;
	float _fVelocity;

public:
	// Constru & Destru
	Move(Entity* pEOwner, Params* params);
	~Move();

	// Methods
	void Update(const Timer& gt)override;
	void UpdateTransform();
	void UpdateDirectorVect(XMFLOAT3 newDirectorVect);
	void UpdateRotation(XMFLOAT3 newRotation);
	XMFLOAT3 GetVectorDirector();
	XMFLOAT3 GetRotation();
};