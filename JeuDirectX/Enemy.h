#pragma once


class Enemy
{
public:

	Enemy(Game* game);
	Entity* GetEntity();

private:

	Entity* _Entity;

};

