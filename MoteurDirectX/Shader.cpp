#include "includes/Pch.h"
#include "includes/Shader.h"

using Microsoft::WRL::ComPtr;


Shader::Shader()
{ }

Shader::~Shader() 
{ }

bool Shader::Init(ComPtr<ID3D12Device> d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize)
{
    BuildRootSignature(d3dDevice);

    BuildDescriptorHeaps(d3dDevice, OpaqueRitemsSize);

    BuildConstantBuffers(d3dDevice, uCbvSrvDescriptorSize, OpaqueRitemsSize);

    return true;
}

void Shader::BuildDescriptorHeaps(ComPtr<ID3D12Device> d3dDevice, UINT OpaqueRitemsSize)
{
    UINT objCount = OpaqueRitemsSize;
    // Need a CBV descriptor for each object for each frame resource,
    // +1 for the perPass CBV for each frame resource.
    UINT numDescriptors = (objCount + 1) * gNumFrameResources;

    // Save an offset to the start of the pass CBVs.  These are the last 3 descriptors.
    uPassCbvOffset = objCount * gNumFrameResources;

    D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
    cbvHeapDesc.NumDescriptors = numDescriptors;
    cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    cbvHeapDesc.NodeMask = 0;
    ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&_CbvHeap)));
}

void Shader::BuildConstantBuffers(ComPtr<ID3D12Device> d3dDevice, UINT uCbvSrvDescriptorSize, UINT OpaqueRitemsSize)
{
    UINT objCBByteSize = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

    //UINT objCount = (UINT)OpaqueRitems.size();
    UINT objCount = OpaqueRitemsSize;

    // Need a CBV descriptor for each object for each frame resource.
    for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
    {
        auto objectCB = _FrameResources[frameIndex]->_ObjectCB->Resource();
        for (UINT i = 0; i < objCount; ++i)
        {
            D3D12_GPU_VIRTUAL_ADDRESS cbAddress = objectCB->GetGPUVirtualAddress();

            // Offset to the ith object constant buffer in the buffer.
            cbAddress += i * objCBByteSize;

            // Offset to the object cbv in the descriptor heap.
            int heapIndex = frameIndex * objCount + i;
            auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_CbvHeap->GetCPUDescriptorHandleForHeapStart());
            handle.Offset(heapIndex, uCbvSrvDescriptorSize);

            D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
            cbvDesc.BufferLocation = cbAddress;
            cbvDesc.SizeInBytes = objCBByteSize;

            d3dDevice->CreateConstantBufferView(&cbvDesc, handle);
        }
    }

    UINT passCBByteSize = Utils::CalcConstantBufferByteSize(sizeof(PassConstants));

    // Last three descriptors are the pass CBVs for each frame resource.
    for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
    {
        auto passCB = _FrameResources[frameIndex]->_PassCB->Resource();
        D3D12_GPU_VIRTUAL_ADDRESS cbAddress = passCB->GetGPUVirtualAddress();

        // Offset to the pass cbv in the descriptor heap.
        int heapIndex = uPassCbvOffset + frameIndex;
        auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_CbvHeap->GetCPUDescriptorHandleForHeapStart());
        handle.Offset(heapIndex, uCbvSrvDescriptorSize);

        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
        cbvDesc.BufferLocation = cbAddress;
        cbvDesc.SizeInBytes = passCBByteSize;

        d3dDevice->CreateConstantBufferView(&cbvDesc, handle);
    }
}

void Shader::BuildRootSignature(ComPtr<ID3D12Device> d3dDevice)
{
    CD3DX12_DESCRIPTOR_RANGE cbvTable0;
    cbvTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

    CD3DX12_DESCRIPTOR_RANGE cbvTable1;
    cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

    // Root parameter can be a table, root descriptor or root constants.
    CD3DX12_ROOT_PARAMETER slotRootParameter[2];

    // Create root CBVs.
    slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable0);
    slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);

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

    ThrowIfFailed(d3dDevice->CreateRootSignature(0, serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(), IID_PPV_ARGS(_RootSignature.GetAddressOf())));
}

void Shader::BuildShadersAndInputLayout()
{
    _Shaders["standardVS"] = Utils::CompileShader(L"..\\MoteurDirectX\\Shaders\\color.hlsl", nullptr, "VS", "vs_5_1");
    _Shaders["opaquePS"] = Utils::CompileShader(L"..\\MoteurDirectX\\Shaders\\color.hlsl", nullptr, "PS", "ps_5_1");
    
    _InputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };
}

void Shader::BuildPSOs(ComPtr<ID3D12Device> d3dDevice, DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

    //
    // PSO for opaque objects.
    //
    ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    opaquePsoDesc.InputLayout = { _InputLayout.data(), (UINT)_InputLayout.size() };
    opaquePsoDesc.pRootSignature = _RootSignature.Get();
    opaquePsoDesc.VS =
    {
        reinterpret_cast<BYTE*>(_Shaders["standardVS"]->GetBufferPointer()),
        _Shaders["standardVS"]->GetBufferSize()
    };
    opaquePsoDesc.PS =
    {
        reinterpret_cast<BYTE*>(_Shaders["opaquePS"]->GetBufferPointer()),
        _Shaders["opaquePS"]->GetBufferSize()
    };
    opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    opaquePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
    opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    opaquePsoDesc.SampleMask = UINT_MAX;
    opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    opaquePsoDesc.NumRenderTargets = 1;
    opaquePsoDesc.RTVFormats[0] = dBackBufferFormat;
    opaquePsoDesc.SampleDesc.Count = b4xMsaaState ? 4 : 1;
    opaquePsoDesc.SampleDesc.Quality = b4xMsaaState ? (u4xMsaaQuality - 1) : 0;
    opaquePsoDesc.DSVFormat = dDepthStencilFormat;
    ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&_PSOs["opaque"])));


    //
    // PSO for opaque wireframe objects.
    //

    D3D12_GRAPHICS_PIPELINE_STATE_DESC opaqueWireframePsoDesc = opaquePsoDesc;
    opaqueWireframePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
    ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&opaqueWireframePsoDesc, IID_PPV_ARGS(&_PSOs["opaque_wireframe"])));
}

/*----------------------------------------------------------*/
/*-------------------------/GETTER\-------------------------*/
/*----------------------------------------------------------*/

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

UploadBuffer<ObjectConstants>* Shader::GetObjects()const
{
    return _ObjectCB;
}

std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> Shader::GetPSOs()
{
    return _PSOs;
}