#include "../includes/Pch.h"
#include "./Move.h"

// Constru & Destru
Move::Move(Entity* pEOwner, Params* params)
	: Component(pEOwner, MOVE), _Params(params)
{

}

void Move::InitComponent(ID3D12Device* d3dDevice)
{
	_v3VectorDirector = _Params->moveParams.directorVector;
	_fVelocity = _Params->moveParams.velocity;
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