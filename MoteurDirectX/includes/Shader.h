#pragma once

#ifndef SHADER_H
#define SHADER_H

//#include <UploadBuffer.h>

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

    // Créer les descriptorHeaps, le ConstantBuffers et les RootSignatures
    bool Init(ComPtr<ID3D12Device> d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize);


public:

    void BuildDescriptorHeaps(ComPtr<ID3D12Device> d3dDevice, UINT OpaqueRitemsSize);
    void BuildConstantBuffers(ComPtr<ID3D12Device> d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize);
    void BuildRootSignature(ComPtr<ID3D12Device> d3dDevice);

    // Compile les fichiers hlsl
    void BuildShadersAndInputLayout();

    void BuildPSOs(ComPtr<ID3D12Device> d3dDevice, DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    /*-------------------------/GETTER\-------------------------*/
    ComPtr<ID3D12RootSignature> GetRootSignature();
    ComPtr<ID3D12DescriptorHeap> GetCbvHeap();
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    UploadBuffer<ObjectConstants>* GetObjects()const;
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> GetPSOs();

public: // Variables

    ComPtr<ID3D12RootSignature> _RootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> _CbvHeap = nullptr;

    UploadBuffer<ObjectConstants>* _ObjectCB = nullptr;

    std::unordered_map<std::string, ComPtr<ID3DBlob>> _Shaders;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> _PSOs;

    std::vector<std::unique_ptr<FrameResource>> _FrameResources;

    UINT uPassCbvOffset = 0;
};

#endif