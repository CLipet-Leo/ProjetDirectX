#pragma once

using namespace DirectX;

class Shader
{
public: // Fonctions
    Shader(Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice, 
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList);
    virtual ~Shader();

    // Cr�er les descriptorHeaps, le ConstantBuffers et les RootSignatures
    bool InitShader();

public:

    void BuildDescriptorHeaps();
    void BuildConstantBuffers();
    void BuildRootSignature();

    void CompileShaders();
    // Cr�er les Inputs
    void CreateInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements);
    void BuildPSO(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    /*
    Utiliser le struct pr�difinis; done
    Cr�er les Heaps; done 
    Cr�er la RootSignature; done
    Cr�er les inputs layout associ� � leurs Vertex done
    !!!!
    Cr�er la g�ometrie ( vertices , indices , struct MeshGeometry ) done
    Cr�er le PSO ( D3D12_GRAPHICS_PIPELINE_STATE_DESC ) done
    */

public: // Variables
    Microsoft::WRL::ComPtr<ID3D12Device> _d3dDevice = nullptr;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _CommandList = nullptr;

    Microsoft::WRL::ComPtr<ID3D12RootSignature> _RootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _CbvHeap = nullptr;

    std::unique_ptr<UploadBuffer<ObjectConstants>> _ObjectCB = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> _serializedRootSig = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> _vsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> _psByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _InputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> _PSO = nullptr;

    // !!!!
    // Unique pointeur d'objet dans le Buffer
    // Unique pointeur de MeshGeometry 
    // !!!!

    // Blob mvs et mps
    // Vector ( D3D12_INPUT_ELEMENT_DESC ) de Layout
    // Pointeur intelligent de PipelineState

    // !!!!
    // Matrices world, view et proj
    XMFLOAT4X4 _World = MathHelper::Identity4x4();
    XMFLOAT4X4 _View = MathHelper::Identity4x4();
    XMFLOAT4X4 _Proj = MathHelper::Identity4x4();

    // Variables math�matique

    // Position de la souris
    // !!!!
};
