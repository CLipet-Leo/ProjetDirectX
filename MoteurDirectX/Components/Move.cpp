#include "../includes/Pch.h"
#include "./Move.h"

// Constru & Destru
Move::Move(Entity* pEOwner, Params* params)
	: Component(pEOwner, MOVE), _v3VectorDirector(params->moveParams.directorVector), _fVelocity(params->moveParams.velocity)
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

void Move::UpdateDirectorVect(XMFLOAT3 newDirectorVect)
{
	_v3VectorDirector = newDirectorVect;
}

XMFLOAT3 Move::GetVectorDirector()
{
	return _v3VectorDirector;
}