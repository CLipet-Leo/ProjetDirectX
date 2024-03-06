#pragma once

class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();

    void Initialize(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    void UpdateCube();

    void RenderCube(D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, 
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _CbvHeap);


    Renderer* _renderer;
    Mesh* _mesh;
    Shader* _shader;
};