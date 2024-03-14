#include "../includes/Pch.h"
#include "MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer(Entity* pEOwner)
    : Component(pEOwner, MESH_RENDERER)
{
    _pMesh = new Mesh();
    _pShader = new Shader();

    _pShader->BuildRootSignature();
    _pShader->CompileShaders();
    _pShader->BuildPSO();
    _Geo = _pMesh->GetGeometry("box");
}

MeshRenderer::~MeshRenderer()
{ }

void MeshRenderer::Update(const Timer& gt)
{
    XMMATRIX world = XMLoadFloat4x4(&_World);

    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
    _ObjectCB->CopyData(_ObjCBIndex, objConstants);
}

void MeshRenderer::Draw(const Timer& gt, ID3D12GraphicsCommandList* cmdList, D3D12_GPU_VIRTUAL_ADDRESS cbPass)
{
    cmdList->SetGraphicsRootSignature(_pShader->GetRootSignature().Get());

    cmdList->IASetVertexBuffers(0, 1, &_Geo->VertexBufferView());
    cmdList->IASetIndexBuffer(&_Geo->IndexBufferView());
    cmdList->IASetPrimitiveTopology(PrimitiveType);

    cmdList->SetGraphicsRootConstantBufferView(0, cbAddress);
    cmdList->SetGraphicsRootConstantBufferView(1, cbPass);

    cmdList->DrawIndexedInstanced(_IndexCount, 1, _StartIndexLocation, _BaseVertexLocation, 0);
}

void MeshRenderer::BuildConstantBuffer(ID3D12Device* d3dDevice)
{
    _ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(d3dDevice, 1, true);

    UINT objCBByteSize = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

    cbAddress = _ObjectCB->Resource()->GetGPUVirtualAddress();
}

Microsoft::WRL::ComPtr<ID3D12PipelineState> MeshRenderer::GetPSO()
{
    return _pShader->GetPSO();
}