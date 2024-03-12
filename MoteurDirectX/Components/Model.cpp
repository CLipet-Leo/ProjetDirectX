#include "../includes/Pch.h"
#include "Model.h"

Model::Model(Entity* pEOwner, Params* params)
	: Component(pEOwner, MODEL)
{
    this->ritem = new RenderItem;
}

void Model::Resize(float fAspectRatio)
{
    // The window resized, so update the aspect ratio and recompute the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, fAspectRatio, 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
}

void Model::Update(const Timer& gt, std::vector<RenderItem*> AllRitems, UploadBuffer<ObjectConstants>* currObjectCB)
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

void Model::Draw(const Timer& gt, ID3D12GraphicsCommandList* cmdList, int iCurrFrameResourceIndex, ID3D12DescriptorHeap* CbvHeap, UINT uCbvSrvDescriptorSize)
{
    auto ri = this->ritem;

    cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
    cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
    cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

    // Offset to the CBV in the descriptor heap for this object and for this frame resource.
    UINT cbvIndex = iCurrFrameResourceIndex * (UINT)sizeof(this->ritem) + ri->ObjCBIndex;
    auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(CbvHeap->GetGPUDescriptorHandleForHeapStart());
    cbvHandle.Offset(cbvIndex, uCbvSrvDescriptorSize);

    cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);

    cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
}