#include "../includes/Pch.h"
#include "Model.h"

Model::Model(Entity* pEOwner, Params* params)
	: Component(pEOwner, MODEL)
{

}

void Model::Update(FrameResource* CurrFrameResource, std::vector<std::unique_ptr<RenderItem>> AllRitems, )
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