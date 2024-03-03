#pragma once

using namespace DirectX;

class Shader : public Renderer
{
public: // Fonctions

    Shader(HINSTANCE hInstance);

    // Créer les descriptorHeaps et les RootSignatures
    void InitShader();

    virtual void OnResize()override;
    virtual void Update(const Timer& gt);
    virtual void Draw(const Timer& gt);

public:
    void BuildDescriptorHeaps();
    void BuildConstantBuffers();
    void BuildRootSignature();

    void CompileShaders();
    void CreateInputLayout(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements);
    void BuildPSO();

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

    Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;


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

    // Variables mathématique

    // Position de la souris
    // !!!!
};
