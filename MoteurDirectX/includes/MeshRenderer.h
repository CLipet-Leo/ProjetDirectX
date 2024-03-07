#pragma once

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Mesh.h"
#include "Shader.h"

class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();

    void Initialize(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList, 
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue, Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DirectCmdListAlloc, 
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CbvHeap,  DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    virtual void Update();

    void UpdateCube();

    void RenderCube(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList, D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView, D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _CbvHeap);


    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();
    float mTheta = 1.5f * XM_PI;
    float mPhi = XM_PIDIV4;
    float mRadius = 5.0f;


    Mesh* _mesh = nullptr;
    Shader* _shader = nullptr;
};

#endif