#include "includes/Pch.h"
#include "includes/Shader.h"

using Microsoft::WRL::ComPtr;


Shader::Shader()
{ }

Shader::~Shader() 
{ }

void Shader::BuildRootSignature()
{
    // Root parameter can be a table, root descriptor or root constants.
    CD3DX12_ROOT_PARAMETER slotRootParameter[2];

    // Create root CBVs.
    slotRootParameter[0].InitAsConstantBufferView(0);
    slotRootParameter[1].InitAsConstantBufferView(1);

    // A root signature is an array of root parameters.
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter, 0, nullptr,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
    ComPtr<ID3DBlob> serializedRootSig = nullptr;
    ComPtr<ID3DBlob> errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
        serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

    if (errorBlob != nullptr)
    {
        ::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    }
    ThrowIfFailed(hr);

    ThrowIfFailed(renderer->CurrentDevice()->CreateRootSignature(0, serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(), IID_PPV_ARGS(_RootSignature.GetAddressOf())));
}

void Shader::CompileShaders()
{
    HRESULT hr = S_OK;

    _vsByteCode = Utils::CompileShader(L"..\\MoteurDirectX\\Shaders\\color.hlsl", nullptr, "VS", "vs_5_0");
    _psByteCode = Utils::CompileShader(L"..\\MoteurDirectX\\Shaders\\color.hlsl", nullptr, "PS", "ps_5_0"); 
    
    _InputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };
}

void Shader::BuildPSO()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
    ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    psoDesc.InputLayout = { _InputLayout.data(), (UINT)_InputLayout.size() };
    psoDesc.pRootSignature = _RootSignature.Get();
    psoDesc.VS =
    {
        reinterpret_cast<BYTE*>(_vsByteCode->GetBufferPointer()),
        _vsByteCode->GetBufferSize()
    };
    psoDesc.PS =
    {
        reinterpret_cast<BYTE*>(_psByteCode->GetBufferPointer()),
        _psByteCode->GetBufferSize()
    };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = renderer->GetBackBufferFormat();
    psoDesc.SampleDesc.Count = renderer->Get4xMsaaState() ? 4 : 1;
    psoDesc.SampleDesc.Quality = renderer->Get4xMsaaState() ? (renderer->Get4xMsaaQuality() - 1) : 0;
    psoDesc.DSVFormat = renderer->GetDepthStencilFormat();
    ThrowIfFailed(renderer->CurrentDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_PSO)));
}

// Getter

ComPtr<ID3D12RootSignature> Shader::GetRootSignature() 
{
    return _RootSignature;
}

std::vector<D3D12_INPUT_ELEMENT_DESC> Shader::GetInputLayout()const 
{
    return _InputLayout;
}

ComPtr<ID3D12PipelineState> Shader::GetPSO()
{
    return _PSO;
}