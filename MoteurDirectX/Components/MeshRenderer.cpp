#include "../includes/Pch.h"
#include "MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer(Entity* pEOwner)
    : Component(pEOwner, MESH_RENDERER)
{

}

void MeshRenderer::InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality)
{
    _pMesh = new Mesh();
    _pShader = new Shader();

    BuildConstantBuffer(d3dDevice);
    _pShader->BuildRootSignature(d3dDevice);
    _pShader->CompileShaders();
    _pMesh->BuildShapeGeometry(d3dDevice, CommandList);
    _pShader->BuildPSO(d3dDevice, b4xMsaaState, u4xMsaaQuality);
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
    cmdList->SetPipelineState(_pShader->GetPSO().Get());

    cmdList->IASetVertexBuffers(0, 1, &_Geo->VertexBufferView());
    cmdList->IASetIndexBuffer(&_Geo->IndexBufferView());
    cmdList->IASetPrimitiveTopology(PrimitiveType);

    cmdList->SetGraphicsRootConstantBufferView(0, cbAddress);

    cmdList->SetGraphicsRootConstantBufferView(1, cbPass);

    cmdList->DrawIndexedInstanced(_IndexCount, 1, _StartIndexLocation, _BaseVertexLocation, 0);
}

void MeshRenderer::BuildConstantBuffer(ID3D12Device* d3dDevice)
{
    _ObjectCB = new UploadBuffer<ObjectConstants>(d3dDevice, 1, true);

    cbAddress = _ObjectCB->Resource()->GetGPUVirtualAddress();
}