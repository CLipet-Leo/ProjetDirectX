// Include needed classes
#include "../includes/Pch.h"
#include "./Camera.h"

// Constru & Destru
Camera::Camera(Entity* ARGpEOwner, Params* ARGpParams)
	: Component(ARGpEOwner, CAMERA),
	_fTheta(ARGpParams->cameraParams.theta), _fPhi(ARGpParams->cameraParams.phi), _fRadius(ARGpParams->cameraParams.radius)
{
	_PrevMousePos = { 0, 0 };
	_fLIMThetaMin = 0.0f;
	_fLIMThetaMax = 0.0f;
	_fLIMPhiMin = 0.1f;
	_fLIMPhiMax = DirectX::XM_PI - 0.1f;
}
Camera::~Camera()
{

}

// This method needs to be called every time the player moves the mouse (or every frame if we go cave-man mode)
void Camera::UpdateCam(int ARGiNewPosX, int ARGiNewPosY)
{
	VSCPrint("=>UpdateCam(int ARGiNewPosX = %d, int ARGiNewPosY = %d)\n", ARGiNewPosX, ARGiNewPosY);

	// Calculates the difference in movement of the mouse
	int iDx = ARGiNewPosX;
	int iDy = ARGiNewPosY;
	VSCPrint("\tiDx = %d ||| iDy = %d\n", iDx, iDy);

	// Applies a factor on the movement of the mouse. You can think of it as the sensibility of the mouse movements.
	float fDegAngleX = 0.25f * static_cast<float>(iDx);
	float fDegAngleY = 0.25f * static_cast<float>(iDy);
	VSCPrint("\tfDegAngleX = %.5f ||| fDegAngleY = %.5f\n", fDegAngleX, fDegAngleY);

	// Converts both distances in radians, so we interpret the "magnitude" of the mouse move by actual Camera movement
	float fRadAngleX = DirectX::XMConvertToRadians(fDegAngleX);
	float fRadAngleY = DirectX::XMConvertToRadians(fDegAngleY);
	VSCPrint("\tfRadAngleX = %.5f ||| fRadAngleY = %.5f\n", fRadAngleX, fRadAngleY);

	// Updates both the angles
	_fTheta += fRadAngleX;
	_fPhi += fRadAngleY;

	// Finally, restrict angles to limit where the player can see
	_fPhi = _fPhi < _fLIMPhiMin ? _fLIMPhiMin : (_fPhi > _fLIMPhiMax ? _fLIMPhiMax : _fPhi);
	/*_fTheta = _fTheta < _fLIMThetaMin ? _fLIMThetaMin : (_fTheta > _fLIMThetaMax ? _fLIMThetaMax : _fTheta);*/
	VSCPrint("\tValue post-clamp : _fTheta = %.5f   _fPhi = %.5f\n", _fTheta, _fPhi);

	// Updates the mouse position
	_PrevMousePos.x += ARGiNewPosX;
	_PrevMousePos.y += ARGiNewPosY;

	VSCPrint("\tPrev Mouse Pos (%d, %d)", _PrevMousePos.x, _PrevMousePos.y);
	VSCPrint("\n<> EXITING...\n");
}

XMMATRIX Camera::CalculateView()
{
	// Calculation of God-knows what
	float x = _fRadius * sinf(_fPhi) * cosf(_fTheta);
	float y = _fRadius * sinf(_fPhi);
	float z = _fRadius * sinf(_fPhi) * sinf(_fTheta);

	// Determines some vectors to build the View matrix
	XMVECTOR pos = XMVectorZero();
	XMVECTOR target = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Returns the result
	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	return view;
}

// Getters to construct View Matrix with the Camera
float Camera::GetTheta() { return _fTheta; }
float Camera::GetPhi() { return _fPhi; }
float Camera::GetRadius() { return _fRadius; }

// Setter to update the mouse position when we want to start moving the Camera around
void Camera::SetMousePos(MousePos ARGStartMousePos)
{
	_PrevMousePos = ARGStartMousePos;
	VSCPrint("Camera::MousePos is at (%d, %d)\n", _PrevMousePos.x, _PrevMousePos.y);
}