#include "stdafx.h"
#include "Window.h"



namespace mylib
{
    Window::Window()
    {
        glfwSetErrorCallback(mylib::Window::error_callback);
    }

    Window::Window(int width, int height, const char * title) :
        width(width), height(height), title(title)
    {
        Window();
    }


    Window::~Window()
    {
        glfwDestroyWindow(_windowHndl);
    }

    void Window::init()
    {
        if (!glfwInit()) {
            std::cerr << "ERROR: (" << __PRETTY_FUNCTION__ << ") glfwInit() returned error"
                << std::endl;
            throw std::runtime_error("glfwInit() returned error");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _windowHndl = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!_windowHndl) {
            std::cerr << "ERROR: (" << __PRETTY_FUNCTION__
                << ") glfwCreateWindow() returned NULL"
                << std::endl;
            throw std::runtime_error("glfwCreateWindow() returned NULL");
        }
        glfwSetKeyCallback(_windowHndl, mylib::Window::key_callback);
        glfwSetInputMode(_windowHndl, GLFW_STICKY_KEYS, 1);
        glfwMakeContextCurrent(_windowHndl);
    }

    GLFWwindow * Window::getWindow()
    {
        return this->_windowHndl;
    }

    void Window::error_callback(int error, const char * description)
    {
        fprintf(stderr, "Error: CODE: 0x%x , %s\n", error, description);
    }

    void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            // clear ESC key pressed event (stickykeyconfigred)
            glfwGetKey(window, GLFW_KEY_ESCAPE);
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

}