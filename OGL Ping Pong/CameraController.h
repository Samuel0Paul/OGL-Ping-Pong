#pragma once

#include "App.h"
#include "Camera.h"

namespace mylib
{
    class CameraController
    {
    public:
        Camera *camera;

        double xpos{0}, ypos{0}, lastFrameTime{0}, deltaTime{0};
        volatile GLfloat lastX{ 0 }, lastY{ 0 }, xoffset{ 0 }, yoffset{ 0 };
        static double sxoffset, syoffset;

        CameraController(
            Camera *camera = nullptr,
            mylib::Window *window = nullptr);
        virtual ~CameraController();

        static void update(CameraController& cc, double time);
        virtual void updateKeyboard(double time);
        virtual void updateMousePosition(double time);
        virtual void updateMouseScroll(double time);

    protected:
        mylib::Window *window{nullptr};

    private:

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    };
}

