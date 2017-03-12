#include "stdafx.h"
#include "FPSCamera.h"



mylib::FPSCamera::FPSCamera(
    int width, int height,
    glm::vec3 position,
    glm::vec3 up,
    GLfloat yaw,
    GLfloat pitch) : Camera(width, height, position, up, yaw, pitch)
{
}

mylib::FPSCamera::FPSCamera(
    int width, int height,
    GLfloat posX,
    GLfloat posY,
    GLfloat posZ,
    GLfloat upX,
    GLfloat upY,
    GLfloat upZ,
    GLfloat yaw,
    GLfloat pitch) : Camera(width, height, posX, posY, posZ, upX, upY, upZ, yaw, pitch)
{
}

mylib::FPSCamera::~FPSCamera()
{
}

void mylib::FPSCamera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    auto y = this->position.y;
    Camera::processKeyboard(direction, deltaTime);
    this->position.y = y;
}
