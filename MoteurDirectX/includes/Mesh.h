#pragma once

using namespace DirectX;

class Mesh
{
public:

	Mesh(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList);
	Mesh(const Mesh& rhs) = delete;
	Mesh& operator=(const Mesh& rhs) = delete;
	virtual ~Mesh();

	SubmeshGeometry GetMesh(const std::string& name)const;

	virtual void BuildGeometry(const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices, const std::string& name);

private:

	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;
protected : 
	SubmeshGeometry* oMesh;
	Microsoft::WRL::ComPtr<ID3D12Device> _d3dDevice;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _CommandList;

};