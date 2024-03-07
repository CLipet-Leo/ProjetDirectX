#pragma once

#ifndef MESH_H
#define MESH_H

using namespace DirectX;

class Mesh
{
public:

	Mesh();
	virtual ~Mesh();

	SubmeshGeometry GetMesh()const;
	std::unique_ptr<MeshGeometry>& GetMeshGeometry();

	virtual void BuildGeometry(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList, 
		const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices);
	void BuildCubeGeometry(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList);


	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

};

#endif