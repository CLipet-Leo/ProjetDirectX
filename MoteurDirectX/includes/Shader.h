#pragma once

using namespace DirectX;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

    // Cr�er les descriptorHeaps et les RootSignatures
    bool InitShader();

public:
    Renderer* engine;

    void BuildDescriptorHeaps();
    void BuildConstantBuffers();
    void BuildRootSignature();

    void CompileShaders();
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

    Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

    std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> mvsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> mpsByteCode = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> mPSO = nullptr;

    // !!!!
    // Unique pointeur d'objet dans le Buffer
    // Unique pointeur de MeshGeometry 
    // !!!!

    // Blob mvs et mps
    // Vector ( D3D12_INPUT_ELEMENT_DESC ) de Layout
    // Pointeur intelligent de PipelineState

    // !!!!
    // Matrices world, view et proj
    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    // Variables math�matique

    // Position de la souris
    // !!!!
};
