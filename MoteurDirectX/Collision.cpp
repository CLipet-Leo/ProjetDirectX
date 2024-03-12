#include "includes/Pch.h"
#include "includes/Collision.h"


Collision::Collision() {}
Collision::~Collision() {}


bool Collision::BoundingSphereCollision(float firstObjBoundingSphere, XMVECTOR firstObjCenterOffset, XMMATRIX& firstObjWorldSpace,
    float secondObjBoundingSphere, XMVECTOR secondObjCenterOffset, XMMATRIX& secondObjWorldSpace)
{
    //Declare local variables
    XMVECTOR world_1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR world_2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    float objectsDistance = 0.0f;

    //Transform the objects world space to objects REAL center in world space
    world_1 = XMVector3TransformCoord(firstObjCenterOffset, firstObjWorldSpace);
    world_2 = XMVector3TransformCoord(secondObjCenterOffset, secondObjWorldSpace);

    //Get the distance between the two objects
    objectsDistance = XMVectorGetX(XMVector3Length(world_1 - world_2));

    //If the distance between the two objects is less than the sum of their bounding spheres...
    if (objectsDistance <= (firstObjBoundingSphere + secondObjBoundingSphere))
        //Return true
        return true;

    //If the bounding spheres are not colliding, return false
    return false;
}