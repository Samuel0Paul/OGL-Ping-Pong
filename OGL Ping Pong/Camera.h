#pragma once

#include "stdafx.h"

namespace mylib
{
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const GLfloat YAW = -90.0f;
    const GLfloat PITCH = 0.0f;
    const GLfloat SPEED = 3.0f;
    const GLfloat SENSITIVITY = 0.05f;
    const GLfloat ZOOM = 45.0f;

    class Camera
    {
    public:
        bool isOrtho{ false };

        int windowWidth, windowHeight;
        glm::vec3 position, front, up, right, worldUp;
        GLfloat yaw{0}, pitch{0}, movementSpeed{0}, mouseSensitivity{0}, zoom{0};

        Camera();
        Camera(
            int width, int height,
            glm::vec3 position,
            glm::vec3 up = glm::vec3(0.f, 1.f, 0.f),
            GLfloat yaw = YAW,
            GLfloat pitch = PITCH);
        Camera(
            int width, int height,
            GLfloat posX,
            GLfloat posY,
            GLfloat posZ,
            GLfloat upX = 0.0f,
            GLfloat upY = -1.0f,
            GLfloat upZ = 0.0f,
            GLfloat yaw = YAW,
            GLfloat pitch = PITCH);
        Camera(const Camera&) = default;
        virtual ~Camera();

        glm::mat4 getViewMatrix();

        virtual glm::mat4 getProjection();

        virtual void processKeyboard(Camera_Movement direction, GLfloat deltaTime);
        virtual void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
        virtual void processMouseScroll(GLfloat yoffset);

    private:
        void updateCameraVectors();
    };
}

