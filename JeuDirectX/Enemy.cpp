#include "Pch.h"
#include "Game.h"
#include "Enemy.h"

Enemy::Enemy(Game* game)
{
    Params params;
    params.moveParams.directorVector = { 1.f, 1.f, 1.f };
    params.moveParams.velocity = 2.f;
    params.moveParams.type = ENEMY;

    std::vector<int> iLtypes;
    iLtypes.push_back(MOVE);

	_Entity = game->InstanciateEntity(iLtypes, &params);
}

Entity* Enemy::GetEntity()
{
	return _Entity;
}