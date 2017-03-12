#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"

extern mylib::GlobalVars mylib::GLOBAL_VARS;

namespace game::objects
{

    class Block
    {
    public:
        const float MOVE_SPEED;

        glm::vec3 pos;
        mylib::Camera* camera;

        Block();
        Block(glm::vec3 pos, mylib::Camera* camera);
        virtual ~Block();
        Block & operator=(const game::objects::Block &);

        virtual void update(double time);
        virtual void render();
        virtual void shutdown();

        float getWidth() { return (glm::vec4(1) * model).x; }
        float getHeight() { return (glm::vec4(3) * model).y; }

    protected:
        GLuint VBO, VAO, EBO;
        mylib::Shader shader;
        glm::mat4 model, view, projection;

    private:
        std::vector<GLfloat> vertices = {
            -0.5f, -1.5f, 0.f,  // 0: LF
            0.5f, -1.5f, 0.f,  // 1: LR
            0.5f,  1.5f, 0.f,  // 2: UR
            -0.5f,  1.5f, 0.f,  // 3: UF
        };
        std::vector<GLuint> indices = {
            0, 1, 2,    // A
            2, 3, 0,    // B
        };
    };


}