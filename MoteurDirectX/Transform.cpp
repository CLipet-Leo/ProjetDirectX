#include "Transform.h"


Transform::Transform() {};
Transform::~Transform() {};

void Transform::Identity() {
	XMStoreFloat4x4(&mScal, XMMatrixIdentity());
	(qScal.x, qScal.y, qScal.z, qScal.w) = (0, 0, 0, 1);
	(mDir.x, mDir.y, mDir.z) = (1, 0, 0);
	(mRight.x, mRight.y, mRight.z) = (0, 1, 0);
	(mUp.x, mUp.y, mUp.z) = (0, 0, 1);
	(qRot.x, qRot.y, qRot.z, qRot.w) = (0, 0, 0, 1);
	XMStoreFloat4x4(&mRot, XMMatrixIdentity());
	(qPos.x, qPos.y, qPos.z, qPos.w) = (0, 0, 0, 1);
	XMStoreFloat4x4(&mPos, XMMatrixIdentity());
	XMStoreFloat4x4(&matrix, XMMatrixIdentity());
};

void Transform::UpdateMatrix() {

	XMMATRIX scale;
	XMMATRIX rotation;
	XMMATRIX position;
	XMMATRIX transformer; // transforme la matrice avec son échelle et sa position
	transformer = scale; // Donne le scaling de la matrice
	transformer *= rotation; // Multiplie la matrice pour avoir la rotation
	transformer *= position; // Multiplie la matrice pour avoir la position
	XMStoreFloat4x4(&matrix, transformer);




};
void Transform::Rotate(float yaw, float pitch, float roll) {
	XMVECTOR quat;
	XMVECTOR rotQuat;


	// Yaw
	XMVECTOR dir;
	dir = XMLoadFloat3(&mDir);
	quat = XMQuaternionRotationAxis(dir, yaw); // Retourne le quaternion selon un axe
	rotQuat = XMQuaternionMultiply(rotQuat, quat); //donne le quaternion après rotation

	// Pitch
	XMVECTOR right;
	right = XMLoadFloat3(&mRight);
	quat = XMQuaternionRotationAxis(right, pitch);
	rotQuat = XMQuaternionMultiply(rotQuat, quat);

	// Roll
	XMVECTOR up;
	up = XMLoadFloat3(&mUp);
	quat = XMQuaternionRotationAxis(up, roll);
	rotQuat = XMQuaternionMultiply(rotQuat, quat);


	// Creation de la matrice de rotation à l'aide des quaternions
	XMVECTOR qCurrentRot;
	qCurrentRot = XMLoadFloat4(&qRot);
	rotQuat = XMQuaternionMultiply(rotQuat, qCurrentRot);

	XMMATRIX rotMat;
	rotMat = XMMatrixRotationQuaternion(rotQuat);
	// stockage des valeurs 
	XMVECTOR storage = XMVectorZero(); // vecteur avec des 0 tu connais ;)

	XMVectorSetX(storage, XMVectorGetX(rotMat.r[0]));
	XMVectorSetY(storage, XMVectorGetY(rotMat.r[0]));
	XMVectorSetZ(storage, XMVectorGetZ(rotMat.r[0]));
	XMStoreFloat3(&mRight, storage);

	XMVectorSetX(storage, XMVectorGetX(rotMat.r[1]));
	XMVectorSetY(storage, XMVectorGetY(rotMat.r[1]));
	XMVectorSetZ(storage, XMVectorGetZ(rotMat.r[1]));
	XMStoreFloat3(&mDir, storage);

	XMVectorSetX(storage, XMVectorGetX(rotMat.r[2]));
	XMVectorSetY(storage, XMVectorGetY(rotMat.r[2]));
	XMVectorSetZ(storage, XMVectorGetZ(rotMat.r[2]));
	XMStoreFloat3(&mUp, storage);

	XMStoreFloat4x4(&mRot, rotMat);



};