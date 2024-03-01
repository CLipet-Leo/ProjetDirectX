#pragma once

using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	virtual bool Initialize()override;

private:
	virtual void OnResize()override;
	virtual void Update(const Timer& gt);
	virtual void Draw(const Timer& gt);

};

