#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "Timer.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

    // Créer les descriptorHeaps, le ConstantBuffers et les RootSignatures
    bool Init(ID3D12Device* d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize);
    void Resize(float fAspectRatio);
    void UpdateMainPassCB(const Timer& gt, int iClientWidth, int iClientHeight, FrameResource* CurrFrameResource);

protected:

    void BuildDescriptorHeaps(ID3D12Device* d3dDevice, UINT OpaqueRitemsSize);
    void BuildConstantBuffers(ID3D12Device* d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize);
    void BuildRootSignature(ID3D12Device* d3dDevice);

    // Compile les fichiers hlsl
    void BuildShadersAndInputLayout();

    void BuildPSOs(ID3D12Device* d3dDevice, DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

public:
    /*-------------------------/GETTER\-------------------------*/
    ComPtr<ID3D12RootSignature> GetRootSignature();
    ComPtr<ID3D12DescriptorHeap> GetCbvHeap();
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    UploadBuffer<ObjectConstants>* GetObjects()const;
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> GetPSOs();

protected: // Variables

    ComPtr<ID3D12RootSignature> _RootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> _CbvHeap = nullptr;

    UploadBuffer<ObjectConstants>* _ObjectCB = nullptr;

    std::unordered_map<std::string, ComPtr<ID3DBlob>> _Shaders;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> _PSOs;

    std::vector<std::unique_ptr<FrameResource>> _FrameResources;

    PassConstants _MainPassCB;

    UINT uPassCbvOffset = 0;

    XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    float mTheta = 1.5f * XM_PI;
    float mPhi = 0.2f * XM_PI;
    float mRadius = 15.0f;
};

#endif