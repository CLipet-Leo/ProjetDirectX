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
	MeshGeometry* GetMeshGeometry();

	void BuildCubeGeometry(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList);
	void BuildPyramidGeometry(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList);
	virtual void BuildGeometry(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList, 
		const std::array<VertexColor, 8> vertices, const std::array<std::uint16_t, 36> indices);


	MeshGeometry* mBoxGeo = nullptr;

};

#endif