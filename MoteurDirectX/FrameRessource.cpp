#include "includes/Pch.h"
#include "includes/FrameRessource.h"

using Microsoft::WRL::ComPtr;

FrameResource::FrameResource(ComPtr<ID3D12Device> device, UINT passCount, UINT objectCount)
{
    ThrowIfFailed(device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_CmdListAlloc.GetAddressOf())));

    _PassCB = std::make_unique<UploadBuffer<PassConstants>>(device, passCount, true);
    _ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, objectCount, true);
}

FrameResource::~FrameResource()
{

}