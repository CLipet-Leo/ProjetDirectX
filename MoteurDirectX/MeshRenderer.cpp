#include "includes/Pch.h"
#include "includes/MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer()
{  
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Initialize(ComPtr<ID3D12Device> d3dDevice, ComPtr<ID3D12GraphicsCommandList> CommandList, ComPtr<ID3D12CommandQueue> CommandQueue, 
    ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc, ComPtr<ID3D12DescriptorHeap> CbvHeap,
    DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    // Reset the command list to prep for initialization commands.
    ThrowIfFailed(CommandList->Reset(DirectCmdListAlloc.Get(), nullptr));
    // Initialisation des shaders
    _shader->InitShader(d3dDevice, CbvHeap);
    _shader->CompileShaders();
    _shader->CreateInputLayout(_shader->GetInputLayout());
    // Initialisation des meshes
    _mesh->BuildCubeGeometry(d3dDevice, CommandList);
    _shader->BuildPSO(dBackBufferFormat, dDepthStencilFormat, b4xMsaaState, u4xMsaaQuality, d3dDevice);

    // Execute the initialization commands.
    ThrowIfFailed(CommandList->Close());
    ID3D12CommandList* cmdsLists[] = { CommandList.Get() };
    CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

void MeshRenderer::Update()
{
    // Convert Spherical to Cartesian coordinates.
    float x = mRadius * sinf(mPhi) * cosf(mTheta);
    float z = mRadius * sinf(mPhi) * sinf(mTheta);
    float y = mRadius * cosf(mPhi);

    // Build the view matrix.
    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&mView, view);

    XMMATRIX world = XMLoadFloat4x4(&mWorld);
    XMMATRIX proj = XMLoadFloat4x4(&mProj);
    XMMATRIX worldViewProj = world * view * proj;

    // Update the constant buffer with the latest worldViewProj matrix.
    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
    _shader->GetObjects()->CopyData(0, objConstants);
}

void MeshRenderer::UpdateCube()
{

}

void MeshRenderer::RenderCube(ComPtr<ID3D12GraphicsCommandList> CommandList, D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, 
    ComPtr<ID3D12DescriptorHeap> _CbvHeap)
{
    // Specify the buffers we are going to render to.
    CommandList->OMSetRenderTargets(1, &CurrentBackBufferView, true, &DepthStencilView);

    ID3D12DescriptorHeap* descriptorHeaps[] = { _CbvHeap.Get() };
    CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    CommandList->SetGraphicsRootSignature(_shader->GetRootSignature().Get());

    CommandList->IASetVertexBuffers(0, 1, &(_mesh->GetMeshGeometry())->VertexBufferView());
    CommandList->IASetIndexBuffer(&(_mesh->GetMeshGeometry())->IndexBufferView());
    CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    CommandList->SetGraphicsRootDescriptorTable(0, _CbvHeap->GetGPUDescriptorHandleForHeapStart());

    CommandList->DrawIndexedInstanced(_mesh->GetMeshGeometry()->DrawArgs["Default"].IndexCount, 1, 0, 0, 0);
}