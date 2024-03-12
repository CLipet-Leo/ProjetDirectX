#pragma once

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Mesh.h"
#include "Shader.h"

class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();

    virtual void Resize(float fAspectRatio);
    virtual void Update(FrameResource* _CurrFrameResource, std::vector<RenderItem*> AllRitems, UploadBuffer<ObjectConstants>* currObjectCB);
    void MeshRenderer::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems, FrameResource* CurrFrameResource, int iCurrFrameResourceIndex, 
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CbvHeap, UINT uCbvSrvDescriptorSize);

public:

    XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    float mTheta = 1.5f * XM_PI;
    float mPhi = 0.2f * XM_PI;
    float mRadius = 15.0f;
};

#endif