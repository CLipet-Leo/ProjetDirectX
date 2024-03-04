#pragma once

using namespace DirectX;
using namespace Microsoft::WRL;

class Mesh
{
public:

	Renderer* engine;

	Mesh();
	Mesh(const Mesh& rhs) = delete;
	Mesh& operator=(const Mesh& rhs) = delete;
	~Mesh();

	virtual void BuildGeometry(const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices, const std::string& name);

private:

	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

};