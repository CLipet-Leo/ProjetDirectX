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

public:
    MeshRenderer(Entity* pEOwner);
    void InitComponent(ID3D12Device* d3dDevice, ID3D12GraphicsCommandList* CommandList, bool b4xMsaaState, UINT u4xMsaaQuality)override;
    ~MeshRenderer();

    virtual void Update(const Timer& gt);
    void Draw(const Timer& gt, ID3D12GraphicsCommandList* cmdList, D3D12_GPU_VIRTUAL_ADDRESS cbPass);
    
    void BuildConstantBuffer(ID3D12Device* d3dDevice);

private:
    XMFLOAT4X4 _World = MathHelper::Identity4x4();

    // Index into GPU constant buffer corresponding to the ObjectCB for this render item.
    UploadBuffer<ObjectConstants>* _ObjectCB = nullptr;
    UINT _ObjCBIndex = 0;
    D3D12_GPU_VIRTUAL_ADDRESS cbAddress;

    MeshGeometry* _Geo = nullptr;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> _PSO = nullptr;

    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT _IndexCount = 0;
    UINT _StartIndexLocation = 0;
    int _BaseVertexLocation = 0;
    Params* _Params;

    Mesh* _pMesh;
    Shader* _pShader;
};