//#include "includes/Pch.h"
//#include "includes/MeshRenderer.h"
//
//MeshRenderer::MeshRenderer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
//{
//    _d3dDevice = device;
//    _commandList = commandList;
//    _mesh = new Mesh(device, commandList);
//    _shader = new Shader(device, commandList);
//}
//
//MeshRenderer::~MeshRenderer()
//{
//    // Clean up resources
//    delete _mesh;
//    delete _shader;
//}
//
//void MeshRenderer::Initialize()
//{
//    // Initialisation des meshes
//    _mesh->BuildGeometry(/* vertices, indices, and name */);
//
//    // Initialisation des shaders
//    _shader->InitShader();
//    _shader->CompileShaders();
//}
//
//void MeshRenderer::UpdateCube()
//{
//
//}
//
//void MeshRenderer::RenderCube()
//{
//    // Set necessary DirectX 12 rendering state (input layout, shaders, etc.)
//    _mesh->GetMesh();
//    _shader->GetShader();
//
//    // Set other rendering states as needed (e.g., constant buffers, textures)
//    _shader->BuildConstantBuffers();
//    _shader->BuildDescriptorHeaps();
//    _shader->BuildPSO(dBackBufferFormat, dDepthStencilFormat, b4xMsaaState, u4xMsaaQuality));
//    _shader->BuildRootSignature();
//    _shader->CompileShaders();
//
//
//    // Issue the draw call
//    _mesh->GetIndexCount();
//}