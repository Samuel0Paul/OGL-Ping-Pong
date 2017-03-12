#pragma once

#include "stdafx.h"

namespace mylib
{
    class Window
    {
    public:
        int width{ 800 }, height{ 600 };
        std::string title{ "Window" };
        bool fullscreen{ false };

        Window();
        Window(int width, int height, const char* title);
        ~Window();

        void init();
        GLFWwindow* getWindow();

        static void error_callback(int error, const char *description);
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    private:
        GLFWwindow *_windowHndl{ nullptr };
    };
}

