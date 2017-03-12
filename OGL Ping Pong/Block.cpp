#include "stdafx.h"
#include "Block.h"
#include "App.h"
#include "OrthoCamera.h"

#define BLK_MOVE_SPD 5.0f

namespace game::objects
{
    Block::Block() :
        MOVE_SPEED(BLK_MOVE_SPD)
    {
    }
    Block::Block(glm::vec3 pos, mylib::Camera* camera) :
        Block()
    {
        this->pos = pos;
        this->camera = camera;

        shader = mylib::Shader({
            std::make_pair(
                "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/block/block.vert",
                GL_VERTEX_SHADER),
            std::make_pair(
                "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/block/block.frag",
                GL_FRAGMENT_SHADER)
        });

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // block data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
            vertices.size() * sizeof(*(vertices.data())),
            vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(*(indices.data())),
            indices.data(), GL_STATIC_DRAW);
        // block attr
        GLint positionAttribLoc{ 0 };
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        positionAttribLoc = glGetAttribLocation(shader.program, "position");
        glEnableVertexAttribArray(positionAttribLoc);
        glVertexAttribPointer(positionAttribLoc, 3,
            GL_FLOAT, GL_FALSE,
            3 * sizeof(*(vertices.data())), ML_BUFFER_OFFSET(0));
        glBindVertexArray(0);
    }

    Block::~Block()
    {
    }

    Block & Block::operator=(const game::objects::Block & x)
    {
        pos = x.pos;
        camera = x.camera;
        VBO = x.VBO;
        VAO = x.VAO;
        EBO = x.EBO;
        shader = x.shader;
        model = x.model;
        view = x.view;
        projection = x.projection;
        vertices = x.vertices;
        indices = x.indices;

        return *this;
    }

    void Block::update(double time)
    {
        view = camera->getViewMatrix();
        projection = camera->getProjection();

        //if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_UP) == GLFW_PRESS) {
        //    if (pos.y + this->getHeight() / 2 < 600 / 2) {
        //        pos.y += 
        //            (MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
        //    }
        //}
        //if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
        //    if (pos.y - this->getHeight() / 2 > - 600 / 2) {
        //        pos.y -= (MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
        //    }
        //}

        model = glm::translate(glm::mat4(), pos);
        model = glm::scale(model, glm::vec3(50));

    }

    void Block::render()
    {
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
            1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
            1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"),
            1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 
            static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, ML_BUFFER_OFFSET(0));
        glBindVertexArray(0);
    }

    void Block::shutdown()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}
