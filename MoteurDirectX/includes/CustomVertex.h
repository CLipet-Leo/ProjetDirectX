#pragma once
#include "Pch.h"

using namespace DirectX;

struct VertexColor
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct VertexUV
{
    XMFLOAT3 pos;
    //texture;
};

struct VertexNorm
{
    XMFLOAT3 pos;
    XMFLOAT3 norm;
};

union Vertex
{
    VertexColor vertex1;
    VertexUV vertex2;
    VertexNorm vertex3;
};

struct VertexBuffer
{
    std::vector<Vertex> vertexList;
};

struct IndiceBuffer
{
    std::vector<int> IndiceList;
};

// Component's params

struct CameraParams
{
    float theta;
    float phi;
    float radius;
};

struct MoveParams
{
    XMFLOAT3 directorVector;
    float velocity;
};

struct GameObjectParams
{
    int iDamage;
    int iHealth;
};

class Component;
class ScriptComponent;

struct CharacterControllerParams
{
    Component* moveCompPtr;
};

struct Params
{
    GameObjectParams gameObjectParams;
    MoveParams moveParams;
    CharacterControllerParams characterControllerParams;
    std::vector<ScriptComponent*> LpScripts;
    CameraParams cameraParams;
};