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

void MeshRenderer::Update(const Timer& gt, UploadBuffer<ObjectConstants>* currObjectCB)
{
    XMMATRIX world = XMLoadFloat4x4(&_World);

    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));

    currObjectCB->CopyData(_ObjCBIndex, objConstants);
}

void MeshRenderer::Draw(const Timer& gt, ID3D12GraphicsCommandList* cmdList, D3D12_GPU_VIRTUAL_ADDRESS cbAddress)
{
    cmdList->IASetVertexBuffers(0, 1, &_Geo->VertexBufferView());
    cmdList->IASetIndexBuffer(&_Geo->IndexBufferView());
    cmdList->IASetPrimitiveTopology(PrimitiveType);

    //auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(CbvHeap->GetGPUDescriptorHandleForHeapStart());
    //cbvHandle.Offset(cbvIndex, uCbvSrvDescriptorSize);
    //cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);

    cmdList->SetGraphicsRootConstantBufferView(0, cbAddress);
    cmdList->SetGraphicsRootConstantBufferView(1, cbAddress);

    cmdList->DrawIndexedInstanced(_IndexCount, 1, _StartIndexLocation, _BaseVertexLocation, 0);
}

Microsoft::WRL::ComPtr<ID3D12PipelineState> MeshRenderer::GetPSO()
{
    return _pShader->GetPSO();
}