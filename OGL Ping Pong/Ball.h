#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"

namespace game::objects
{

    class Ball
    {
    public:
        const float MOVE_SPEED;

        glm::vec3 pos, velocity;
        mylib::Camera* camera;

        Ball();
        Ball(glm::vec3 pos, float radius, int sides);
        Ball & operator=(const game::objects::Ball &);
        virtual ~Ball();

        virtual void update(double time);
        virtual void render();
        virtual void shutdown();

        float getRadius() { return (glm::vec4(radius) * model).x; }

    protected:
        GLuint VBO, VAO;
        mylib::Shader shader;
        glm::mat4 model, view, projection;

        float radius;

        std::vector<GLfloat> vertices;
    };
}