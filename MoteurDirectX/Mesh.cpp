#include "includes/Pch.h"
#include "includes/Mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}


void Mesh::BuildGeometry(const std::vector<VertexColor>& vertices, const std::vector<std::uint16_t>& indices, const std::string& name)
{
    const UINT vbByteSize = static_cast<UINT>(vertices.size()) * sizeof(VertexColor);
    const UINT ibByteSize = static_cast<UINT>(indices.size()) * sizeof(std::uint16_t);

    auto mBoxGeo = std::make_unique<MeshGeometry>();
    mBoxGeo->Name = name;

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
    CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
    CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

    mBoxGeo->VertexBufferGPU = Utils::CreateDefaultBuffer(engine->CurrentDevice(),
        engine->CurrentCommandList(), vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);

    mBoxGeo->IndexBufferGPU = Utils::CreateDefaultBuffer(engine->CurrentDevice(),
        engine->CurrentCommandList(), indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

    mBoxGeo->VertexByteStride = sizeof(VertexColor);
    mBoxGeo->VertexBufferByteSize = vbByteSize;
    mBoxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    mBoxGeo->IndexBufferByteSize = ibByteSize;

    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    mBoxGeo->DrawArgs[name] = submesh;
}

// pour cr�er un mesh tu fais comme �a ;) !

//std::array<Vertex, 8> boxVertices = { Vertex1,Vertex2, VertexN }; // voir exemple chap 6
//std::array<std::uint16_t, 6> boxIndices = {     
//    // Front face
//    0, 1, 2,
//    0, 2, 3, 
//    ECT
//};
//BuildCustomGeometry(boxVertices, boxIndices, L"boxGeo"); // et la boum tu as un carr�, un rectangle, un chteumeule !
