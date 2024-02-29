#pragma once
#include "Pch.h"

using Microsoft::WRL::ComPtr;

using namespace DirectX;

class Shader
{
public: // Fonctions

    Shader(HINSTANCE hInstance);

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

    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

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
