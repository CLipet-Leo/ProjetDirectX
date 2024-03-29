﻿
#include "includes/Pch.h"
#include "includes/Mesh.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX::PackedVector;

Mesh::Mesh() {}

Mesh::~Mesh() {}

Mesh::MeshData* Mesh::CreateBox(float width, float height, float depth, uint32 numSubdivisions)
{
    MeshData* meshData = new MeshData();

    Vertex v[24];

    float w2 = 0.5f * width;
    float h2 = 0.5f * height;
    float d2 = 0.5f * depth;

    // Fill in the front face vertex data.
    v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Fill in the back face vertex data.
    v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Fill in the top face vertex data.
    v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Fill in the bottom face vertex data.
    v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Fill in the left face vertex data.
    v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
    v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
    v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
    v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

    // Fill in the right face vertex data.
    v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    meshData->Vertices.assign(&v[0], &v[24]);

    //
    // Create the indices.
    //

    uint32 i[36];

    // Fill in the front face index data
    i[0] = 0; i[1] = 1; i[2] = 2;
    i[3] = 0; i[4] = 2; i[5] = 3;

    // Fill in the back face index data
    i[6] = 4; i[7] = 5; i[8] = 6;
    i[9] = 4; i[10] = 6; i[11] = 7;

    // Fill in the top face index data
    i[12] = 8; i[13] = 9; i[14] = 10;
    i[15] = 8; i[16] = 10; i[17] = 11;

    // Fill in the bottom face index data
    i[18] = 12; i[19] = 13; i[20] = 14;
    i[21] = 12; i[22] = 14; i[23] = 15;

    // Fill in the left face index data
    i[24] = 16; i[25] = 17; i[26] = 18;
    i[27] = 16; i[28] = 18; i[29] = 19;

    // Fill in the right face index data
    i[30] = 20; i[31] = 21; i[32] = 22;
    i[33] = 20; i[34] = 22; i[35] = 23;

    meshData->Indices32.assign(&i[0], &i[36]);

    // Put a cap on the number of subdivisions.
    numSubdivisions = std::min<uint32>(numSubdivisions, 6u);

    for (uint32 i = 0; i < numSubdivisions; ++i)
        Subdivide(*meshData);

    return meshData;
}

Mesh::MeshData* Mesh::CreateSphere(float radius, uint32 sliceCount, uint32 stackCount)
{
    MeshData* meshData = new MeshData();

    //
    // Compute the vertices stating at the top pole and moving down the stacks.
    //

    // Poles: note that there will be texture coordinate distortion as there is
    // not a unique point on the texture map to assign to the pole when mapping
    // a rectangular texture onto a sphere.
    Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    meshData->Vertices.push_back(topVertex);

    float phiStep = XM_PI / stackCount;
    float thetaStep = 2.0f * XM_PI / sliceCount;

    // Compute vertices for each stack ring (do not count the poles as rings).
    for (uint32 i = 1; i <= stackCount - 1; ++i)
    {
        float phi = i * phiStep;

        // Vertices of ring.
        for (uint32 j = 0; j <= sliceCount; ++j)
        {
            float theta = j * thetaStep;

            Vertex v;

            // spherical to cartesian
            v.Position.x = radius * sinf(phi) * cosf(theta);
            v.Position.y = radius * cosf(phi);
            v.Position.z = radius * sinf(phi) * sinf(theta);

            // Partial derivative of P with respect to theta
            v.TangentU.x = -radius * sinf(phi) * sinf(theta);
            v.TangentU.y = 0.0f;
            v.TangentU.z = +radius * sinf(phi) * cosf(theta);

            XMVECTOR T = XMLoadFloat3(&v.TangentU);
            XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

            XMVECTOR p = XMLoadFloat3(&v.Position);
            XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

            v.TexC.x = theta / XM_2PI;
            v.TexC.y = phi / XM_PI;

            meshData->Vertices.push_back(v);
        }
    }

    meshData->Vertices.push_back(bottomVertex);

    //
    // Compute indices for top stack.  The top stack was written first to the vertex buffer
    // and connects the top pole to the first ring.
    //

    for (uint32 i = 1; i <= sliceCount; ++i)
    {
        meshData->Indices32.push_back(0);
        meshData->Indices32.push_back(i + 1);
        meshData->Indices32.push_back(i);
    }

    //
    // Compute indices for inner stacks (not connected to poles).
    //

    // Offset the indices to the index of the first vertex in the first ring.
    // This is just skipping the top pole vertex.
    uint32 baseIndex = 1;
    uint32 ringVertexCount = sliceCount + 1;
    for (uint32 i = 0; i < stackCount - 2; ++i)
    {
        for (uint32 j = 0; j < sliceCount; ++j)
        {
            meshData->Indices32.push_back(baseIndex + i * ringVertexCount + j);
            meshData->Indices32.push_back(baseIndex + i * ringVertexCount + j + 1);
            meshData->Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            meshData->Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            meshData->Indices32.push_back(baseIndex + i * ringVertexCount + j + 1);
            meshData->Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    //
    // Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
    // and connects the bottom pole to the bottom ring.
    //

    // South pole vertex was added last.
    uint32 southPoleIndex = (uint32)meshData->Vertices.size() - 1;

    // Offset the indices to the index of the first vertex in the last ring.
    baseIndex = southPoleIndex - ringVertexCount;

    for (uint32 i = 0; i < sliceCount; ++i)
    {
        meshData->Indices32.push_back(southPoleIndex);
        meshData->Indices32.push_back(baseIndex + i);
        meshData->Indices32.push_back(baseIndex + i + 1);
    }

    return meshData;
}


void Mesh::Subdivide(MeshData& meshData)
{
    // Save a copy of the input geometry.
    MeshData inputCopy = meshData;

    meshData.Vertices.resize(0);
    meshData.Indices32.resize(0);

    //       v1
    //       *
    //      / \
	//     /   \
	//  m0*-----*m1
    //   / \   / \
	//  /   \ /   \
	// *-----*-----*
    // v0    m2     v2

    uint32 numTris = (uint32)inputCopy.Indices32.size() / 3;
    for (uint32 i = 0; i < numTris; ++i)
    {
        Vertex v0 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 0]];
        Vertex v1 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 1]];
        Vertex v2 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 2]];
      
        //
        // Generate the midpoints.
        //

        Vertex m0 = MidPoint(v0, v1);
        Vertex m1 = MidPoint(v1, v2);
        Vertex m2 = MidPoint(v0, v2);

        //
        // Add new geometry.
        //

        meshData.Vertices.push_back(v0); // 0
        meshData.Vertices.push_back(v1); // 1
        meshData.Vertices.push_back(v2); // 2
        meshData.Vertices.push_back(m0); // 3
        meshData.Vertices.push_back(m1); // 4
        meshData.Vertices.push_back(m2); // 5

        meshData.Indices32.push_back(i * 6 + 0);
        meshData.Indices32.push_back(i * 6 + 3);
        meshData.Indices32.push_back(i * 6 + 5);

        meshData.Indices32.push_back(i * 6 + 3);
        meshData.Indices32.push_back(i * 6 + 4);
        meshData.Indices32.push_back(i * 6 + 5);

        meshData.Indices32.push_back(i * 6 + 5);
        meshData.Indices32.push_back(i * 6 + 4);
        meshData.Indices32.push_back(i * 6 + 2);

        meshData.Indices32.push_back(i * 6 + 3);
        meshData.Indices32.push_back(i * 6 + 1);
        meshData.Indices32.push_back(i * 6 + 4);
    }
}

Mesh::Vertex Mesh::MidPoint(const Vertex& v0, const Vertex& v1)
{
    XMVECTOR p0 = XMLoadFloat3(&v0.Position);
    XMVECTOR p1 = XMLoadFloat3(&v1.Position);

    XMVECTOR n0 = XMLoadFloat3(&v0.Normal);
    XMVECTOR n1 = XMLoadFloat3(&v1.Normal);

    XMVECTOR tan0 = XMLoadFloat3(&v0.TangentU);
    XMVECTOR tan1 = XMLoadFloat3(&v1.TangentU);

    XMVECTOR tex0 = XMLoadFloat2(&v0.TexC);
    XMVECTOR tex1 = XMLoadFloat2(&v1.TexC);

    // Compute the midpoints of all the attributes.  Vectors need to be normalized
    // since linear interpolating can make them not unit length.  
    XMVECTOR pos = 0.5f * (p0 + p1);
    XMVECTOR normal = XMVector3Normalize(0.5f * (n0 + n1));
    XMVECTOR tangent = XMVector3Normalize(0.5f * (tan0 + tan1));
    XMVECTOR tex = 0.5f * (tex0 + tex1);

    Vertex v;
    XMStoreFloat3(&v.Position, pos);
    XMStoreFloat3(&v.Normal, normal);
    XMStoreFloat3(&v.TangentU, tangent);
    XMStoreFloat2(&v.TexC, tex);

    return v;
}

void Mesh::BuildShapeGeometry(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList)
{
    // Part box
    MeshData* box = CreateBox(1.5f, 0.5f, 1.5f, 3);
    UINT boxVertexOffset = 0;
    UINT boxIndexOffset = 0;

    auto totalVertexCount = box->Vertices.size();

    std::vector<VertexColor> vertices(totalVertexCount);

    UINT k = 0;
    for (size_t i = 0; i < box->Vertices.size(); ++i, ++k)
    {
        vertices[k].pos = box->Vertices[i].Position;
        vertices[k].color = XMFLOAT4(DirectX::Colors::DarkGreen);
    }

    std::vector<std::uint16_t> indices;
    indices.insert(indices.end(), std::begin(box->GetIndices16()), std::end(box->GetIndices16()));

    const UINT vbByteSize = (UINT)vertices.size() * sizeof(VertexColor);
    const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

    auto boxGeo = new MeshGeometry;
    boxGeo->Name = "box";

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeo->VertexBufferCPU));
    CopyMemory(boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeo->IndexBufferCPU));
    CopyMemory(boxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

    boxGeo->VertexBufferGPU = Utils::CreateDefaultBuffer(d3dDevice,
        CommandList, vertices.data(), vbByteSize, boxGeo->VertexBufferUploader);

    boxGeo->IndexBufferGPU = Utils::CreateDefaultBuffer(d3dDevice,
        CommandList, indices.data(), ibByteSize, boxGeo->IndexBufferUploader);

    boxGeo->VertexByteStride = sizeof(VertexColor);
    boxGeo->VertexBufferByteSize = vbByteSize;
    boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    boxGeo->IndexBufferByteSize = ibByteSize;
    //boxGeo->DisposeUploaders();
    _Geometries.push_back(boxGeo);

    // Part sphere
    MeshData* sphere = CreateSphere(1.0f, 20, 20);
    UINT sphereVertexOffset = 0;
    UINT sphereIndexOffset = 0;

    auto totalSphereVertexCount = sphere->Vertices.size();

    std::vector<VertexColor> sphereVertices(totalSphereVertexCount);

    k = 0;
    for (size_t i = 0; i < sphere->Vertices.size(); ++i, ++k)
    {
        sphereVertices[k].pos = sphere->Vertices[i].Position;
        sphereVertices[k].color = XMFLOAT4(DirectX::Colors::DarkBlue);
    }

    std::vector<std::uint16_t> sphereIndices;
    sphereIndices.insert(sphereIndices.end(), std::begin(sphere->GetIndices16()), std::end(sphere->GetIndices16()));

    const UINT sphereVbByteSize = (UINT)sphereVertices.size() * sizeof(VertexColor);
    const UINT sphereIbByteSize = (UINT)sphereIndices.size() * sizeof(std::uint16_t);

    auto sphereGeo = new MeshGeometry;
    sphereGeo->Name = "sphere";

    ThrowIfFailed(D3DCreateBlob(sphereVbByteSize, &sphereGeo->VertexBufferCPU));
    CopyMemory(sphereGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), sphereVbByteSize);

    ThrowIfFailed(D3DCreateBlob(sphereIbByteSize, &sphereGeo->IndexBufferCPU));
    CopyMemory(sphereGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), sphereIbByteSize);

    sphereGeo->VertexBufferGPU = Utils::CreateDefaultBuffer(d3dDevice,
        CommandList, sphereVertices.data(), sphereVbByteSize, sphereGeo->VertexBufferUploader);

    sphereGeo->IndexBufferGPU = Utils::CreateDefaultBuffer(d3dDevice,
        CommandList, sphereIndices.data(), sphereIbByteSize, sphereGeo->IndexBufferUploader);

    sphereGeo->VertexByteStride = sizeof(VertexColor);
    sphereGeo->VertexBufferByteSize = sphereVbByteSize;
    sphereGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    sphereGeo->IndexBufferByteSize = sphereIbByteSize;

    //sphereGeo->DisposeUploaders();
    _Geometries.push_back(sphereGeo);
}

MeshGeometry* Mesh::GetGeometry(const std::string& geometryName)
{
    for (MeshGeometry* geometry : _Geometries)
    {
        if (geometry->Name == geometryName)
        {
            return geometry;
        }
    }

    return nullptr;
}
