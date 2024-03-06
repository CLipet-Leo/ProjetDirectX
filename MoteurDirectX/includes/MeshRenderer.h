#pragma once
#include "Mesh.h"
#include "Shader.h"

class MeshRenderer
{
public:
    MeshRenderer(Microsoft::WRL::ComPtr<ID3D12Device> device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc);
    ~MeshRenderer();

    void Initialize(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    void UpdateCube();

    void RenderCube(D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, 
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _CbvHeap);


	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _CommandList;

	Microsoft::WRL::ComPtr<ID3D12Device> _d3dDevice;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

	Shader* _shader;
	Mesh* _mesh;
};