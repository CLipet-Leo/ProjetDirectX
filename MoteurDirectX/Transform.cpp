#include "includes/Pch.h"
#include "includes/Transform.h"


Transform::Transform() {
	Identity();
};
Transform::~Transform() {};

void Transform::Identity() {
	XMStoreFloat4x4(&mScal, XMMatrixIdentity());
	(qScal.x, qScal.y, qScal.z, qScal.w) = (0.f, 0.f, 0.f, 1.f);
	(mDir.x, mDir.y, mDir.z) = (1.f, 0.f, 0.f);
	(mRight.x, mRight.y, mRight.z) = (0.f, 1.f, 0.f);
	(mUp.x, mUp.y, mUp.z) = (0.f, 0.f, 1.f);
	(qRot.x, qRot.y, qRot.z, qRot.w) = (0.f, 0.f, 0.f, 1.f);
	XMStoreFloat4x4(&mRot, XMMatrixIdentity());
	(qPos.x, qPos.y, qPos.z, qPos.w) = (0.f, 0.f, 0.f, 1.f);
	XMStoreFloat4x4(&mPos, XMMatrixIdentity());
	XMStoreFloat4x4(&matrix, XMMatrixIdentity());
};

void Transform::Rotate(float yaw, float pitch, float roll) {

	XMVECTOR quat;
	XMVECTOR rotQuat = XMVectorZero();

	// Roll
	XMVECTOR up;
	up = XMLoadFloat3(&mUp);
	quat = XMQuaternionRotationAxis(up, roll);
	rotQuat = XMQuaternionMultiply(rotQuat, quat);

	// Pitch
	XMVECTOR right;
	right = XMLoadFloat3(&mRight);
	quat = XMQuaternionRotationAxis(right, pitch);
	rotQuat = XMQuaternionMultiply(rotQuat, quat);

	// Yaw
	XMVECTOR dir;
	dir = XMLoadFloat3(&mDir);
	quat = XMQuaternionRotationAxis(dir, yaw); // Retourne le quaternion selon un axe
	rotQuat = quat;//donne le quaternion apr�s rotation


	// Creation de la matrice de rotation à l'aide des quaternions
	XMVECTOR qCurrentRot = XMLoadFloat4(&qRot);
	rotQuat = XMQuaternionMultiply(rotQuat, qCurrentRot);

	XMMATRIX rotMat = XMMatrixRotationQuaternion(rotQuat);

	// No need to normalize the vectors here
	XMStoreFloat3(&mRight, rotMat.r[0]);
	XMStoreFloat3(&mDir, rotMat.r[1]);
	XMStoreFloat3(&mUp, rotMat.r[2]);

	XMStoreFloat4x4(&mRot, rotMat);
};

void Transform::UpdateMatrix() {


	// Create scaling matrix
	XMMATRIX scaleMat = XMLoadFloat4x4(&mScal);

	// Create rotation matrix
	XMMATRIX rotationMat = XMLoadFloat4x4(&mRot);

	// Create translation matrix
	XMMATRIX positionMat = XMLoadFloat4x4(&mPos);

	XMMATRIX transformer; // transforme la matrice avec son �chelle et sa position
	transformer = scaleMat; // Donne le scaling de la matrice
	transformer *= rotationMat; // Multiplie la matrice pour avoir la rotation
	transformer *= positionMat; // Multiplie la matrice pour avoir la position

	XMMATRIX currentMatrix = XMLoadFloat4x4(&matrix);
	XMMATRIX newFinalMatrix = currentMatrix * transformer; // Permet de gérer en fonction du temps
	XMStoreFloat4x4(&matrix, newFinalMatrix);

	//XMMATRIX newFinalMatrix = transformer;
	//XMStoreFloat4x4(&matrix, newFinalMatrix); méthode instantanée
};
