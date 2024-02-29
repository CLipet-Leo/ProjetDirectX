#pragma once

// Forward declarations
class Component;

class Move : public Component;
{
private:
	XMFLOAT3 _v3VectorDirector;
	float _fVelocity;

public:
	// Constru & Destru
	Move::Move();
	Move::~Move();

	// Methods
	void Move::UpdateTransform();
};