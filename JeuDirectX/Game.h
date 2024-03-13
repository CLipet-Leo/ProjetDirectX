#pragma once
#include "Shader.h"

/**/ /* <[)  BAPT CODE :3  (]> */ /**/
// Forward decalration of namespace and its classes
//namespace DirectX
//{
//	class XMFLOAT4X4;
//}
/**/ /* <[)  BAPT CODE :3  (]> */ /**/
using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	virtual ~Game();

	virtual bool Initialize()override;

	std::vector<Enemy*> _LpEntity;

	void spawnEnemy();

private:


};

