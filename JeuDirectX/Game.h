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

private:

	/**/ /* <[)  BAPT CODE :3  (]> */ /**/
	// Various central DirectX Matrixes
	// All those Matrixes will be initalized in the constructor, unlike how the book does (because the book doesn't have a .h)
	XMFLOAT4X4* _pM4World;
	XMFLOAT4X4* _pM4View;
	XMFLOAT4X4* _pM4Proj;
	/**/ /* <[)  BAPT CODE :3  (]> */ /**/

};

