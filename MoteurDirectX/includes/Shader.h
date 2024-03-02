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

    void BuildShadersAndInputLayout();
    void BuildPSO();

    /*
    Utiliser le struct prédifinis;
    Créer les Heaps;
    Créer la RootSignature;
    Créer les inputs layout associé à leurs Vertex
    !!!!
    Créer la géometrie ( vertices , indices , struct MeshGeometry )
    Créer le PSO ( D3D12_GRAPHICS_PIPELINE_STATE_DESC )
    */

public: // Variables

    Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

    // !!!!
    // Unique pointeur d'objet dans le Buffer
    // Unique pointeur de MeshGeometry 
    // !!!!

    // Blob mvs et mps
    // Vector ( D3D12_INPUT_ELEMENT_DESC ) de Layout
    // Pointeur intelligent de PipelineState

    // !!!!
    // Matrices world, view et proj
    XMFLOAT4X4 WorldViewProj;

    // Variables mathématique

    // Position de la souris
    // !!!!
};
