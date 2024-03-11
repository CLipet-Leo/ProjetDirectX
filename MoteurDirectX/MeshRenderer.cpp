#include "includes/Pch.h"
#include "includes/MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer()
{
    _mesh = new Mesh;
    _shader = new Shader;
}

MeshRenderer::~MeshRenderer()
{ }

bool MeshRenderer::Initialize(ComPtr<ID3D12Device> d3dDevice, ComPtr<ID3D12GraphicsCommandList> CommandList, ComPtr<ID3D12CommandQueue> CommandQueue, 
    ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc,  DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    // Initialisation des shaders
    if (!_shader->InitShader(d3dDevice))
        return false;
    _shader->CompileShaders();
    //_shader->CreateInputLayout(_shader->GetInputLayout());
    // Initialisation des meshes
    _mesh->BuildCubeGeometry(d3dDevice, CommandList);
    _shader->BuildPSO(dBackBufferFormat, dDepthStencilFormat, b4xMsaaState, u4xMsaaQuality, d3dDevice);

    return true;
}

void MeshRenderer::OnResize(float fAspectRatio)
{
    // The window resized, so update the aspect ratio and recompute the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, fAspectRatio, 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
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

void MeshRenderer::RenderCube(ComPtr<ID3D12GraphicsCommandList> CommandList, D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView)
{
    // Specify the buffers we are going to render to.
    CommandList->OMSetRenderTargets(1, &CurrentBackBufferView, true, &DepthStencilView);

    ID3D12DescriptorHeap* descriptorHeaps[] = { _shader->GetCbvHeap().Get()};
    CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    CommandList->SetGraphicsRootSignature(_shader->GetRootSignature().Get());

    int passCbvIndex = PassCbvOffset + CurrFrameResourceIndex;
    auto passCbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(_shader->GetCbvHeap()->GetGPUDescriptorHandleForHeapStart());
    passCbvHandle.Offset(passCbvIndex, mCbvSrvUavDescriptorSize);
    CommandList->SetGraphicsRootDescriptorTable(1, passCbvHandle);

    DrawRenderItems(mCommandList.Get(), mOpaqueRitems);
}

Microsoft::WRL::ComPtr<ID3D12PipelineState> MeshRenderer::GetPSO()
{
    return _shader->GetPSO();
}