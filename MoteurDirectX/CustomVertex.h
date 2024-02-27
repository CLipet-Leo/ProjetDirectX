#pragma once

#include "IncludeLib.h"
#include <DirectXPackedVector.h>
#include <vector>

using namespace DirectX;

struct VertexColor
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct VertexUV
{
    XMFLOAT3 pos;
    //texture;
};

struct VertexNorm
{
    XMFLOAT3 pos;
    XMFLOAT3 norm;
};

union Vertex
{
    VertexColor vertex1;
    VertexUV vertex2;
    VertexNorm vertex3;
};

struct VertexBuffer
{
    std::vector<Vertex> vertexList;
};

struct IndiceBuffer
{
    std::vector<int> IndiceList;
};
