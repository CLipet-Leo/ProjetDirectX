#include "includes/Pch.h"
#include "includes/Mesh.h"

Mesh::Mesh(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList)
    : _d3dDevice(d3dDevice), _CommandList(CommandList) {}

Mesh::~Mesh() {}

SubmeshGeometry Mesh::GetMesh() const
{
    return mBoxGeo->DrawArgs.begin()->second;
}

void Mesh::BuildGeometry(const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices)
{
    const UINT vbByteSize = static_cast<UINT>(vertices.size()) * sizeof(VertexColor);
    const UINT ibByteSize = static_cast<UINT>(indices.size()) * sizeof(std::uint16_t);

    mBoxGeo = std::make_unique<MeshGeometry>();

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
    CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
    CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

    mBoxGeo->VertexBufferGPU = Utils::CreateDefaultBuffer(_d3dDevice.Get(),
        _CommandList.Get(), vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);

    mBoxGeo->IndexBufferGPU = Utils::CreateDefaultBuffer(_d3dDevice.Get(),
        _CommandList.Get(), indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

    mBoxGeo->VertexByteStride = sizeof(VertexColor);
    mBoxGeo->VertexBufferByteSize = vbByteSize;
    mBoxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    mBoxGeo->IndexBufferByteSize = ibByteSize;

    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    mBoxGeo->DrawArgs["Default"] = submesh;
}

void Mesh::BuildCubeGeometry()
{
    std::vector<VertexColor> vertices =
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

    std::vector<std::uint16_t>  indices =
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
    BuildGeometry(vertices, indices);
}
