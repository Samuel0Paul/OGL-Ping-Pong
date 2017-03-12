#include "stdafx.h"
#include "Camera.h"



mylib::Camera::Camera() :
    isOrtho(false)
{
}

mylib::Camera::Camera(int width, int height,
    glm::vec3 position,
    glm::vec3 up,
    GLfloat yaw,
    GLfloat pitch) : front(glm::vec3(0.f, 0.f, -1.0f)),
    movementSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM),
    windowWidth(width),
    windowHeight(height)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();
}

mylib::Camera::Camera(int width, int height,
    GLfloat posX, GLfloat posY, GLfloat posZ,
    GLfloat upX, GLfloat upY, GLfloat upZ,
    GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM),
    windowWidth(width),
    windowHeight(height)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();
}

mylib::Camera::~Camera()
{
}

glm::mat4 mylib::Camera::getViewMatrix()
{
    return glm::lookAt(
        this->position,
        this->position + this->front,
        this->up);
}

glm::mat4 mylib::Camera::getProjection()
{
    std::clog << "Camera::getProjection() " << std::endl;
    return glm::perspective(zoom,
        static_cast<GLfloat>(windowWidth) / windowHeight,
        0.1f, 100.0f);
}

void mylib::Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->movementSpeed * deltaTime;
    if (direction == FORWARD)
        this->position += this->front * velocity;
    if (direction == BACKWARD)
        this->position -= this->front * velocity;
    if (direction == LEFT)
        this->position -= this->right * velocity;
    if (direction == RIGHT)
        this->position += this->right * velocity;
}

void mylib::Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->mouseSensitivity;
    yoffset *= this->mouseSensitivity;

    //this->yaw += xoffset;
    this->yaw = std::fmod((this->yaw + xoffset), (GLfloat)360.0f);
    this->pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
}

void mylib::Camera::processMouseScroll(GLfloat yoffset)
{
    /*if (this->zoom >= 1.0f && this->zoom <= 45.0f)
    this->zoom -= yoffset;
    if (this->zoom <= 1.0f)
    this->zoom = 1.0f;
    if (this->zoom >= 45.0f)
    this->zoom = 45.0f;
    */
    yoffset *= this->mouseSensitivity;
    this->position.y += yoffset;

    this->updateCameraVectors();
}

void mylib::Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
    front.y = std::sin(glm::radians(this->pitch));
    front.z = std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));

    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
