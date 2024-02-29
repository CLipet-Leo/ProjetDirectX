#pragma once

#include "Pch.h"

using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	virtual bool Initialize()override;

private:
	virtual void Update(const Timer& gt);
	virtual void Draw(const Timer& gt);

};

