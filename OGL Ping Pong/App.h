#pragma once

#include "stdafx.h"

#include "Window.h"
#include "Camera.h"

#define ML_BUFFER_OFFSET(idx) \
			static_cast<const GLvoid*>(static_cast<char*>(0) + (idx))

namespace mylib
{
    inline const GLvoid* BUFFER_OFFSET(const std::size_t& idx);

    struct GlobalVars
    {
        GLFWwindow* activeGLFWwindow;
        mylib::Camera* camera;

        GlobalVars()
        {
            lastTime = glfwGetTime();
        }

        void updateTime()
        {
            timeOffset = glfwGetTime() - lastTime;
            lastTime = glfwGetTime();
        }
        
        double getTimeOffset()
        {
            return timeOffset;
        }

    private:
        double lastTime, timeOffset;
    };

    extern GlobalVars GLOBAL_VARS;

    class App
    {
    public:
        Window window;

        App() = delete;
        App(mylib::Window&& window);
        virtual ~App();

        static void run(App& app);
        int getWindowWidth();
        int getWindowHeight();

        virtual void startup() {}
        virtual void update(double) {}
        virtual void render() {}
        virtual void shutdown() {}
//        GLuint program;
    };
}

