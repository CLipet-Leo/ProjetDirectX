#include "includes/Pch.h"
#include "includes/MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer()
{  
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Initialize(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    // Reset the command list to prep for initialization commands.
    ThrowIfFailed(_renderer->CurrentCommandList()->Reset(_renderer->GetCommandAlloc().Get(), nullptr));
    // Initialisation des shaders
    _shader->InitShader();
    _shader->CompileShaders();
    _shader->CreateInputLayout(_shader->GetInputLayout());
    // Initialisation des meshes
    _mesh->BuildCubeGeometry();
    _shader->BuildPSO(dBackBufferFormat, dDepthStencilFormat, b4xMsaaState, u4xMsaaQuality);

    // Execute the initialization commands.
    ThrowIfFailed(_renderer->CurrentCommandList()->Close());
    ID3D12CommandList* cmdsLists[] = { _renderer->CurrentCommandList().Get() };
    _renderer->GetCommandQueue()->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

void MeshRenderer::UpdateCube()
{

}

void MeshRenderer::RenderCube(D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, ComPtr<ID3D12DescriptorHeap> _CbvHeap)
{
    // Specify the buffers we are going to render to.
    _renderer->CurrentCommandList()->OMSetRenderTargets(1, &CurrentBackBufferView, true, &DepthStencilView);

    ID3D12DescriptorHeap* descriptorHeaps[] = { _CbvHeap.Get() };
    _renderer->CurrentCommandList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    _renderer->CurrentCommandList()->SetGraphicsRootSignature(_shader->GetRootSignature().Get());

    _renderer->CurrentCommandList()->IASetVertexBuffers(0, 1, &(_mesh->GetMeshGeometry())->VertexBufferView());
    _renderer->CurrentCommandList()->IASetIndexBuffer(&(_mesh->GetMeshGeometry())->IndexBufferView());
    _renderer->CurrentCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    _renderer->CurrentCommandList()->SetGraphicsRootDescriptorTable(0, _CbvHeap->GetGPUDescriptorHandleForHeapStart());

    _renderer->CurrentCommandList()->DrawIndexedInstanced(_mesh->GetMeshGeometry()->DrawArgs["Default"].IndexCount, 1, 0, 0, 0);
}