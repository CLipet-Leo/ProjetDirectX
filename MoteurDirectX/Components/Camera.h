#pragma once

// Struct to have a clean way to store the mouse's position
struct MousePos
{
    int x;
    int y;
};

class Camera : public Component
{
public:
    // Constru & Destru
    Camera::Camera(Entity* ARGpEOwner, Params* ARGpParams);
    Camera::~Camera();

    // Getters to construct View Matrix with the Camera
    float Camera::GetTheta();
    float Camera::GetPhi();
    float Camera::GetRadius();

    // Setter to update the mouse position when we want to start moving the Camera around
    void Camera::SetMousePos(MousePos ARGStartMousePos);

    // This method needs to be called every time the player moves the mouse (or every frame if we go cave-man mode)
    void Camera::UpdateCam(int ARGiNewPosX, int ARGiNewPosY);

private:
    // Variables needed to rotate the Camera around
    // Phi is the angle for Up & Down, Theta is the angle for Left & Right
    float _fTheta;
    float _fPhi;
    float _fRadius;

    // Mouse pos stuff to do cool calculus
    MousePos _PrevMousePos;

    // Limits that both the angles can reach, restricting the player's view
    float _fLIMThetaMin;
    float _fLIMThetaMax;
    float _fLIMPhiMin;
    float _fLIMPhiMax;
};