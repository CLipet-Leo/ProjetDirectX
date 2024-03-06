#pragma once
using namespace DirectX;

class Mesh
{
public:

	Mesh();
	Mesh(const Mesh& rhs) = delete;
	Mesh& operator=(const Mesh& rhs) = delete;
	virtual ~Mesh();

	SubmeshGeometry GetMesh()const;
	std::unique_ptr<MeshGeometry>& GetMeshGeometry();

	virtual void BuildGeometry(const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices);
	void BuildCubeGeometry();

	Renderer* _renderer;

private:

	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

};