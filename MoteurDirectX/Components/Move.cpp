#include "../includes/Pch.h"
#include "./Move.h"

// Constru & Destru
Move::Move(Entity* pEOwner, Params* params)
	: Component(pEOwner, MOVE), _v3VectorDirector(params->moveParams.directorVector), _fVelocity(params->moveParams.velocity), _pTransform(params->moveParams.rotation)
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
	_pEOwner->UpdateTransform(&_v3VectorDirector, &_pTransform);
}

void Move::UpdateDirectorVect(XMFLOAT3 newDirectorVect)
{
	_v3VectorDirector = newDirectorVect;
}

void Move::UpdateRotation(XMFLOAT3 newRotation)
{
	_pTransform = newRotation;
}


XMFLOAT3 Move::GetVectorDirector()
{
	return _v3VectorDirector;
}

XMFLOAT3 Move::GetRotation()
{
	return _pTransform;
}