#include "stdafx.h"
#include "CameraController.h"

double mylib::CameraController::sxoffset = 0;
double mylib::CameraController::syoffset = 0;

mylib::CameraController::CameraController(
    Camera *camera,
    mylib::Window *window) : 
    camera(std::move(camera)),
    window(window)
{
    if (window != nullptr)
    {
        // for keyboard
        lastFrameTime = glfwGetTime();

        // for mouse
        glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window->getWindow(), window->width, window->height);
        glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
        lastX = static_cast<GLfloat>(xpos);
        lastY = static_cast<GLfloat>(ypos);

        // for scroll
        glfwSetScrollCallback(window->getWindow(), (GLFWscrollfun)scroll_callback);
    }
}

mylib::CameraController::~CameraController()
{
}

void mylib::CameraController::update(CameraController & cc, double time)
{
    if (!cc.camera->isOrtho)
    {
        cc.updateKeyboard(time);
        cc.updateMousePosition(time);
        cc.updateMouseScroll(time);
    }
}

void mylib::CameraController::updateKeyboard(double time)
{
    if (window != nullptr)
    {
        this->deltaTime = time - lastFrameTime;
        this->lastFrameTime = time;

        // W - key press
        if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->processKeyboard(mylib::FORWARD, static_cast<float>(deltaTime));
        }
        // S - key press
        if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            camera->processKeyboard(mylib::BACKWARD, static_cast<float>(deltaTime));
        }
        // A - key press
        if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->processKeyboard(mylib::LEFT, static_cast<float>(deltaTime));
        }
        // D - key press
        if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->processKeyboard(mylib::RIGHT, static_cast<float>(deltaTime));
        }
    }
}

void mylib::CameraController::updateMousePosition(double time)
{
    if (window != nullptr)
    {
        glfwGetCursorPos(window->getWindow(), &this->xpos, &this->ypos);
        this->xoffset = static_cast<GLfloat>(this->xpos - this->lastX);
        // reversed y cord, botton to top
        this->yoffset = static_cast<GLfloat>(this->lastY - this->ypos);
        this->lastX = static_cast<GLfloat>(this->xpos);
        this->lastY = static_cast<GLfloat>(this->ypos);

        camera->processMouseMovement(this->xoffset, this->yoffset);
    }
}

void mylib::CameraController::updateMouseScroll(double time)
{
    // refer scroll_callback()
    camera->processMouseScroll(static_cast<float>(this->syoffset));
    sxoffset = 0;
    syoffset = 0;
}

void mylib::CameraController::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
    sxoffset = xoffset;
    syoffset = yoffset;
}
