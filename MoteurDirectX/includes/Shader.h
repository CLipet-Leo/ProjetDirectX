#pragma once

using namespace DirectX;

class Shader : public Renderer
{
public: // Fonctions

    Shader(HINSTANCE hInstance);

    // Cr�er les descriptorHeaps et les RootSignatures
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
    Utiliser le struct pr�difinis;
    Cr�er les Heaps;
    Cr�er la RootSignature;
    Cr�er les inputs layout associ� � leurs Vertex
    !!!!
    Cr�er la g�ometrie ( vertices , indices , struct MeshGeometry )
    Cr�er le PSO ( D3D12_GRAPHICS_PIPELINE_STATE_DESC )
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

    // Variables math�matique

    // Position de la souris
    // !!!!
};
