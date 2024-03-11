#pragma once

#ifndef SHADER_H
#define SHADER_H

//#include <UploadBuffer.h>

using namespace DirectX;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

    // Créer les descriptorHeaps, le ConstantBuffers et les RootSignatures
    bool InitShader(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);


public:

    void BuildDescriptorHeaps(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);
    void BuildConstantBuffers(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);
    void BuildRootSignature(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);

    // Compile les fichiers hlsl
    void CompileShaders();
    // Créer les Inputs
    void CreateInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements);

    void BuildPSO(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality, Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);

    /*-------------------------/GETTER\-------------------------*/
    Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature();
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetCbvHeap();
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    UploadBuffer<ObjectConstants>* GetObjects()const;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO();

public: // Variables

    Microsoft::WRL::ComPtr<ID3D12RootSignature> _RootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _CbvHeap = nullptr;

    UploadBuffer<ObjectConstants>* _ObjectCB = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> _vsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _psByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> _PSO = nullptr;

};

#endif