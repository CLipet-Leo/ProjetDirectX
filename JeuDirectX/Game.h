#pragma once
#include "Shader.h"

using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	virtual bool Initialize()override;

private:

};

