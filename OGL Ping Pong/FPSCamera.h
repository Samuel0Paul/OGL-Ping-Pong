#pragma once
#include "stdafx.h"
#include "Camera.h"

namespace mylib
{
    class FPSCamera :
        public mylib::Camera
    {
    public:
        FPSCamera(int width, int height, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
            glm::vec3 up = glm::vec3(0.f, 1.f, 0.f),
            GLfloat yaw = YAW,
            GLfloat pitch = PITCH);
        FPSCamera(
            int width, int height, 
            GLfloat posX,
            GLfloat posY,
            GLfloat posZ,
            GLfloat upX = 0.0f,
            GLfloat upY = -1.0f,
            GLfloat upZ = 0.0f,
            GLfloat yaw = YAW,
            GLfloat pitch = PITCH);
        virtual ~FPSCamera();

        virtual void processKeyboard(Camera_Movement direction, GLfloat deltaTime) override;
    };


}