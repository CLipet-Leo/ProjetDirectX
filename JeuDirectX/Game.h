#pragma once
#include "Shader.h"

using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	virtual ~Game();

	virtual bool Initialize()override;

private:

};

