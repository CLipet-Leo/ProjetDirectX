#pragma once
using namespace DirectX;

class Shader
{
public: // Fonctions
    Shader();
    virtual ~Shader();

    // Créer les descriptorHeaps, le ConstantBuffers et les RootSignatures
    bool InitShader();


public:

    void BuildDescriptorHeaps();
    void BuildConstantBuffers();
    void BuildRootSignature();
    Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature();

    void CompileShaders();
    // Créer les Inputs
    void CreateInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements);
    std::vector<D3D12_INPUT_ELEMENT_DESC> GetInputLayout()const;
    void BuildPSO(DXGI_FORMAT dBackBufferFormat, DXGI_FORMAT dDepthStencilFormat, bool b4xMsaaState, UINT u4xMsaaQuality);

    /*
    Utiliser le struct prédifinis; done
    Créer les Heaps; done 
    Créer la RootSignature; done
    Créer les inputs layout associé à leurs Vertex done
    !!!!
    Créer la géometrie ( vertices , indices , struct MeshGeometry ) done
    Créer le PSO ( D3D12_GRAPHICS_PIPELINE_STATE_DESC ) done
    */

public: // Variables

    Microsoft::WRL::ComPtr<ID3D12RootSignature> _RootSignature = nullptr;

    std::unique_ptr<UploadBuffer<ObjectConstants>> _ObjectCB = nullptr;

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


    // Variables mathématique
    // Position de la souris
    // !!!!

    Renderer* _renderer;
};
