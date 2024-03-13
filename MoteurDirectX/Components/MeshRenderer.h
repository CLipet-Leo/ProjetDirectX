#pragma once

struct RenderItem
{
    RenderItem() = default;

    // World matrix of the shape that describes the object's local space
    // relative to the world space, which defines the position, orientation,
    // and scale of the object in the world.
};

class MeshRenderer : public Component
{
private:
    XMFLOAT4X4 _World = MathHelper::Identity4x4();

    // Index into GPU constant buffer corresponding to the ObjectCB for this render item.
    UINT _ObjCBIndex = -1;

    MeshGeometry* _Geo = nullptr;

    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT _IndexCount = 0;
    UINT _StartIndexLocation = 0;
    int _BaseVertexLocation = 0;


public:
    MeshRenderer(Entity* pEOwner);
    ~MeshRenderer();

    virtual void Update(const Timer& gt, UploadBuffer<ObjectConstants>* currObjectCB);
    void Draw(const Timer& gt, ID3D12GraphicsCommandList* cmdList, D3D12_GPU_VIRTUAL_ADDRESS cbAddress);

    Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO();

public:

    Mesh* _pMesh;
    Shader* _pShader;
};