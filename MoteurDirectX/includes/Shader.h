#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "Renderer.h"

using namespace DirectX;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

public:

    void BuildRootSignature(ID3D12Device* d3dDevice);

    // Compile les fichiers hlsl
    void CompileShaders();
    void BuildPSO(ID3D12Device* d3dDevice, bool b4xMsaaState, UINT u4xMsaaQuality);

    Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature();
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO();
    Microsoft::WRL::ComPtr<ID3DBlob> GetvsByteCode();
    Microsoft::WRL::ComPtr<ID3DBlob> GetpsByteCode();

public: // Variables

    Microsoft::WRL::ComPtr<ID3D12RootSignature> _RootSignature = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> _vsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _psByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> _PSO = nullptr;

};

#endif