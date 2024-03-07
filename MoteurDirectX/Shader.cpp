#include "includes/Pch.h"
#include "includes/Shader.h"

using Microsoft::WRL::ComPtr;


Shader::Shader()
{ }

Shader::~Shader() 
{ }

bool Shader::InitShader(ComPtr<ID3D12Device> d3dDevice)
{
    BuildDescriptorHeaps(d3dDevice);

    BuildConstantBuffers(d3dDevice);

    BuildRootSignature(d3dDevice);

    return true;
}

void Shader::BuildDescriptorHeaps(ComPtr<ID3D12Device> d3dDevice)
{
    D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
    cbvHeapDesc.NumDescriptors = 1;
    cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    cbvHeapDesc.NodeMask = 0;
    ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&_CbvHeap)));
}

void Shader::BuildConstantBuffers(ComPtr<ID3D12Device> d3dDevice)
{
    _ObjectCB = new UploadBuffer<ObjectConstants>(d3dDevice, 1, true);

    UINT objCBByteSize = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

    D3D12_GPU_VIRTUAL_ADDRESS cbAddress = _ObjectCB->Resource()->GetGPUVirtualAddress();
    // Offset to the ith object constant buffer in the buffer.
    int boxCBufIndex = 0;
    cbAddress += boxCBufIndex * objCBByteSize;

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
    cbvDesc.BufferLocation = cbAddress;
    cbvDesc.SizeInBytes = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

    d3dDevice->CreateConstantBufferView(
        &cbvDesc,
        _CbvHeap->GetCPUDescriptorHandleForHeapStart());
}

void Shader::BuildRootSignature(ComPtr<ID3D12Device> d3dDevice)
{
    // Shader programs typically require resources as input (constant buffers,
    // textures, samplers).  The root signature defines the resources the shader
    // programs expect.  If we think of the shader programs as a function, and
    // the input resources as function parameters, then the root signature can be
    // thought of as defining the function signature.  

    // Root parameter can be a table, root descriptor or root constants.
    CD3DX12_ROOT_PARAMETER slotRootParameter[1];

    // Create a single descriptor table of CBVs.
    CD3DX12_DESCRIPTOR_RANGE cbvTable;
    cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
    slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);

    // A root signature is an array of root parameters.
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
    Microsoft::WRL::ComPtr<ID3DBlob> _serializedRootSig = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob = nullptr;

    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
        _serializedRootSig.GetAddressOf(), _errorBlob.GetAddressOf());

    if (_errorBlob != nullptr)
    {
        ::OutputDebugStringA((char*)_errorBlob->GetBufferPointer());
    }
    ThrowIfFailed(hr);

    ThrowIfFailed(d3dDevice->CreateRootSignature(
        0,
        _serializedRootSig->GetBufferPointer(),
        _serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&_RootSignature)));
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

void Shader::CreateInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements)
{
    //_InputLayout = inputElements;
    

}

void Shader::BuildPSO(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality, ComPtr<ID3D12Device> d3dDevice)
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
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = dBackBufferFormat;
    psoDesc.SampleDesc.Count = b4xMsaaState ? 4 : 1;
    psoDesc.SampleDesc.Quality = b4xMsaaState ? (u4xMsaaQuality - 1) : 0;
    psoDesc.DSVFormat = dDepthStencilFormat;
    ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_PSO)));
}

// Petit exemple d'usage messire : 
//std::vector<D3D12_INPUT_ELEMENT_DESC> inputElements = {
//    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
//};
//
//Shader shaderInstance;
//shaderInstance.CreateInputLayout(inputElements); 

ComPtr<ID3D12RootSignature> Shader::GetRootSignature() 
{
    return _RootSignature;
}

ComPtr<ID3D12DescriptorHeap> Shader::GetCbvHeap()
{
    return _CbvHeap;
}

std::vector<D3D12_INPUT_ELEMENT_DESC> Shader::GetInputLayout()const 
{
    return _InputLayout;
}

UploadBuffer<ObjectConstants>* Shader::GetObjects() 
{
    return _ObjectCB;
}