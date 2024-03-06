#include "includes/Pch.h"
#include "includes/MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer(ComPtr<ID3D12Device> device, ComPtr<ID3D12GraphicsCommandList> commandList, ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc)
    : _d3dDevice(device), _CommandList(commandList), _DirectCmdListAlloc(DirectCmdListAlloc)
{
    
    _mesh = new Mesh(device, commandList);
    _shader = new Shader(device, commandList);
}

MeshRenderer::~MeshRenderer()
{
    // Clean up resources
    delete _mesh;
    delete _shader;
}

void MeshRenderer::Initialize(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    // Reset the command list to prep for initialization commands.
    ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), nullptr));
    // Initialisation des shaders
    _shader->InitShader();
    _shader->CompileShaders();
    _shader->CreateInputLayout(_InputLayout);
    // Initialisation des meshes
    _mesh->BuildCubeGeometry();
    _shader->BuildPSO(dBackBufferFormat, dDepthStencilFormat, b4xMsaaState, u4xMsaaQuality);

}

void MeshRenderer::UpdateCube()
{

}

void MeshRenderer::RenderCube(D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, ComPtr<ID3D12DescriptorHeap> _CbvHeap)
{
    // Specify the buffers we are going to render to.
    _CommandList->OMSetRenderTargets(1, &CurrentBackBufferView, true, &DepthStencilView);

    ID3D12DescriptorHeap* descriptorHeaps[] = { _CbvHeap.Get() };
    _CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    _CommandList->SetGraphicsRootSignature(_shader->GetRootSignature().Get());

    _CommandList->IASetVertexBuffers(0, 1, &(_mesh->GetMeshGeometry())->VertexBufferView());
    _CommandList->IASetIndexBuffer(&(_mesh->GetMeshGeometry())->IndexBufferView());
    _CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    _CommandList->SetGraphicsRootDescriptorTable(0, _CbvHeap->GetGPUDescriptorHandleForHeapStart());

    _CommandList->DrawIndexedInstanced(_mesh->GetMeshGeometry()->DrawArgs["Default"].IndexCount, 1, 0, 0, 0);
}