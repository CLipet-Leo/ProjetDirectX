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

public:

    void BuildRootSignature(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);

    // Compile les fichiers hlsl
    void CompileShaders();
    void BuildPSO(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality, Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice);

    Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature();
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO();

public: // Variables

    Microsoft::WRL::ComPtr<ID3D12RootSignature> _RootSignature = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> _vsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _psByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> _PSO = nullptr;

};

#endif