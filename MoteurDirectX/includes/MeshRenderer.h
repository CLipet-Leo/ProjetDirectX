//#pragma once
//#include"Mesh.h"
//class MeshRenderer
//{
//public:
//    MeshRenderer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
//    ~MeshRenderer();
//
//    void Initialize();
//
//    void UpdateCube( );
//
//    void RenderCube();
//
//
//	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _DirectCmdListAlloc;
//	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _CommandList;
//
//	Microsoft::WRL::ComPtr<ID3D12Device> _d3dDevice;
//	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _commandList;
//
//    bool b4xMsaaState = false;    // 4X MSAA enabled
//    UINT u4xMsaaQuality = 0;      // quality level of 4X MSAA
//
//    DXGI_FORMAT dBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
//    DXGI_FORMAT dDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
//
//	Shader* _shader;
//	Mesh* _mesh;
//    Renderer* _renderer;
//};