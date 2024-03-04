#pragma once

/**/ /* <[)  BAPT CODE :3  (]> */ /**/
// Forward decalration of namespace and its classes
namespace DirectX
{
	class XMFLOAT4X4;
}
/**/ /* <[)  BAPT CODE :3  (]> */ /**/
using namespace DirectX;

class Game : public Renderer
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	virtual bool Initialize()override;

private:

	/**/ /* <[)  BAPT CODE :3  (]> */ /**/
	// Various central DirectX Matrixes
	// All those Matrixes will be initalized in the constructor, unlike how the book does (because the book doesn't have a .h)
	XMFLOAT4X4* _pM4World;
	XMFLOAT4X4* _pM4View;
	XMFLOAT4X4* _pM4Proj;
	/**/ /* <[)  BAPT CODE :3  (]> */ /**/

	// Methods to run theApp
	virtual void OnResize()override;
	virtual void Update(const Timer& gt);
	virtual void Draw(const Timer& gt);

};

