#pragma once
#include "customVertex.h"
#include "D3DUtils.h"

class Shader
{
public: // Fonctions
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
    /*
    Pointeur intelligent de RootSignatue
    Pointeur intelligent de Heaps

    !!!!
    Unique pointeur d'objet dans le Buffer
    Unique pointeur de MeshGeometry 
    !!!!

    Blob mvs et mps
    Vector ( D3D12_INPUT_ELEMENT_DESC ) de Layout
    Pointeur intelligent de PipelineState

    !!!!
    Matrices world, view et proj

    Variables math�matique

    Position de la souris
    !!!!
    */
};
