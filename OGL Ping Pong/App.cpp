#include "stdafx.h"
#include "App.h"

namespace mylib
{
    extern GlobalVars GLOBAL_VARS = {};

    inline const GLvoid* BUFFER_OFFSET(const std::size_t& idx)
    {
        return
            static_cast<const GLvoid*>(static_cast<char*>(0) + (idx));
    }

    App::App(mylib::Window && window) :
        window(window)
    {
    }

    App::~App()
    {
    }

    void App::run(App & app)
    {
        app.window.init();
        app.startup();
        GLOBAL_VARS.activeGLFWwindow = app.window.getWindow();

        while (!glfwWindowShouldClose(app.window.getWindow())) {
            app.update(glfwGetTime());
            app.render();

            glfwSwapBuffers(app.window.getWindow());
            glfwPollEvents();
        }

        app.shutdown();
    }

    int App::getWindowWidth()
    {
        return static_cast<int>(this->window.width);
    }

    int App::getWindowHeight()
    {
        return static_cast<int>(this->window.height);
    }

}