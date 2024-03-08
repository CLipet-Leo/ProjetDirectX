#include "includes/Pch.h"
#include "includes/Mesh.h"

using Microsoft::WRL::ComPtr;

Mesh::Mesh() {}

Mesh::~Mesh() {}

SubmeshGeometry Mesh::GetMesh() const
{
    return mBoxGeo->DrawArgs.begin()->second;
}

MeshGeometry* Mesh::GetMeshGeometry() {
    return mBoxGeo;
}

void Mesh::BuildCubeGeometry(ComPtr<ID3D12Device> d3dDevice, ComPtr<ID3D12GraphicsCommandList> CommandList)
{
    std::array<VertexColor, 8> vertices =
    {
        VertexColor({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
        VertexColor({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
        VertexColor({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
        VertexColor({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
        VertexColor({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
        VertexColor({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
        VertexColor({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
        VertexColor({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
    };

    std::array<std::uint16_t, 36>  indices =
    {
        // front face
        0, 1, 2,
        0, 2, 3,

        // back face
        4, 6, 5,
        4, 7, 6,

        // left face
        4, 5, 1,
        4, 1, 0,

        // right face
        3, 2, 6,
        3, 6, 7,

        // top face
        1, 5, 6,
        1, 6, 2,

        // bottom face
        4, 0, 3,
        4, 3, 7
    };

    // Build the cube geometry using the generic BuildGeometry function
    BuildGeometry(d3dDevice, CommandList, vertices, indices);
}


void Mesh::BuildPyramidGeometry(ComPtr<ID3D12Device> d3dDevice, ComPtr<ID3D12GraphicsCommandList> CommandList)
{
    std::array<VertexColor, 8> vertices =
    {
        VertexColor({ XMFLOAT3(-5.0f, -5.0f, +0.0f), XMFLOAT4(Colors::White) }),
        VertexColor({ XMFLOAT3(+0.0f, +5.0f, +0.0f), XMFLOAT4(Colors::Black) }),
        VertexColor({ XMFLOAT3(+5.0f, -5.0f, +0.0f), XMFLOAT4(Colors::Red) }),
        VertexColor({ XMFLOAT3(+5.0f, -5.0f, +0.0f), XMFLOAT4(Colors::Green) }),
        VertexColor({ XMFLOAT3(+10.0f, +5.0f, +0.0f), XMFLOAT4(Colors::Blue) }),
        VertexColor({ XMFLOAT3(+10.0f, +5.0f, +0.0f), XMFLOAT4(Colors::Yellow) }),
        VertexColor({ XMFLOAT3(+15.0f, -5.0f, +0.0f), XMFLOAT4(Colors::Cyan) }),
        VertexColor({ XMFLOAT3(+20.0f, +5.0f, +0.0f), XMFLOAT4(Colors::Magenta) })
    };

    std::array<std::uint16_t, 36>  indices =
    {
        // front face
        0, 1, 2,
        0, 2, 3,

        // back face
        4, 6, 5,
        4, 7, 6,

        // left face
        4, 5, 1,
        4, 1, 0,

        // right face
        3, 2, 6,
        3, 6, 7,

        // top face
        1, 5, 6,
        1, 6, 2,

        // bottom face
        4, 0, 3,
        4, 3, 7
    };

    // Build the cube geometry using the generic BuildGeometry function
    BuildGeometry(d3dDevice, CommandList, vertices, indices);
}