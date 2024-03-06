#include "../includes/Pch.h"
#include "./Move.h"

// Constru & Destru
Move::Move(Entity* pEOwner, MoveParams params)
	: Component(pEOwner, MOVE), _v3VectorDirector(params.directorVector)
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