#include "../includes/Pch.h"
#include "./Move.h"

// Constru & Destru
Move::Move(Entity* pEOwner, XMFLOAT3 ARGv3VectorDirector, float ARGfVelocity)
	: Component(pEOwner, MOVE), _v3VectorDirector(ARGv3VectorDirector)
{

}

Move::~Move()
{

}

void Move::Update(const Timer& gt)
{

}

void Move::UpdateTransform()
{
	_pEOwner->UpdateTransform(&_v3VectorDirector);
}

XMFLOAT3 Move::GetVectorDirector()
{
	return _v3VectorDirector;
}