#include "includes/Pch.h"
#include "includes/MeshRenderer.h"

using Microsoft::WRL::ComPtr;

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{ }

void MeshRenderer::Resize(float fAspectRatio)
{
    // The window resized, so update the aspect ratio and recompute the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, fAspectRatio, 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
}

void MeshRenderer::Update(FrameResource* CurrFrameResource, std::vector<RenderItem*> AllRitems, UploadBuffer<ObjectConstants>* currObjectCB)
{
    for (auto& e : AllRitems)
    {
        // Only update the cbuffer data if the constants have changed.  
        // This needs to be tracked per frame resource.
        if (e->NumFramesDirty > 0)
        {
            XMMATRIX world = XMLoadFloat4x4(&e->World);

            ObjectConstants objConstants;
            XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));

            currObjectCB->CopyData(e->ObjCBIndex, objConstants);

            // Next FrameResource need to be updated too.
            e->NumFramesDirty--;
        }
    }
}

void MeshRenderer::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems, FrameResource* CurrFrameResource, int iCurrFrameResourceIndex, ComPtr<ID3D12DescriptorHeap> CbvHeap, UINT uCbvSrvDescriptorSize)
{
    
        auto ri = ritems[i];

        cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
        cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
        cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

        // Offset to the CBV in the descriptor heap for this object and for this frame resource.
        UINT cbvIndex = iCurrFrameResourceIndex * (UINT)ritems.size() + ri->ObjCBIndex;
        auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(CbvHeap->GetGPUDescriptorHandleForHeapStart());
        cbvHandle.Offset(cbvIndex, uCbvSrvDescriptorSize);

        cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);

        cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
}