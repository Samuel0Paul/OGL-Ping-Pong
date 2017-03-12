#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"
#include "Ball.h"

#include "PingPongGame.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#define BALL_MOVE_SPD 1.20f

namespace game::objects
{
    Ball::Ball() :
        MOVE_SPEED(BALL_MOVE_SPD)
    {
    }

    Ball::Ball(glm::vec3 pos, float radius, int sides) :
        Ball()
    {
        this->pos = pos;
        this->radius = radius;

        this->velocity = glm::vec3(0.5f, 1.f, 0.0f);

        float x, y;
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(radius);
        vertices.push_back(0);
        vertices.push_back(0);
        for (int i = 0; i < sides; ++i) {
            float ang = static_cast<float>(M_PI) * 2.0f / sides * i;
            x = glm::cos(ang) * radius;
            y = -glm::sin(ang) * radius;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0);
        }
        vertices.push_back(radius);
        vertices.push_back(0);
        vertices.push_back(0);

        shader = mylib::Shader({
            std::make_pair(
                "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/ball/ball.vert",
                GL_VERTEX_SHADER),
            std::make_pair(
                "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/ball/ball.frag",
                GL_FRAGMENT_SHADER)
        });

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
            vertices.size() * sizeof(*(vertices.data())),
            vertices.data(), GL_STATIC_DRAW);
        GLint positionAttribLoc{ 0 };
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        positionAttribLoc = glGetAttribLocation(shader.program, "position");
        glEnableVertexAttribArray(positionAttribLoc);
        glVertexAttribPointer(positionAttribLoc, 3,
            GL_FLOAT, GL_FALSE,
            3 * sizeof(*(vertices.data())), ML_BUFFER_OFFSET(0));
        glBindVertexArray(0);
    }

    Ball & Ball::operator=(const game::objects::Ball & x)
    {
        this->radius = x.radius;
        pos = x.pos;
        velocity = x.velocity;
        camera = x.camera;
        VBO = x.VBO;
        VAO = x.VAO;
        shader = x.shader;
        model = x.model;
        view = x.view;
        projection = x.projection;
        vertices = x.vertices;

        return *this;
    }


    Ball::~Ball()
    {
    }

    void Ball::update(double time)
    {
        camera = mylib::GLOBAL_VARS.camera;

        model = glm::translate(glm::mat4(), pos);
        model = glm::scale(model, glm::vec3(50));

        if (pos.x + (glm::vec4(radius) * model).x > 400 && velocity.x > 0) {
            velocity.x *= -1;
            game::GAME_GLOBALS.pointsTeamA += 1;
        }
        if (pos.x - (glm::vec4(radius) * model).x < -400 && velocity.x < 0) {
            velocity.x *= -1;
            game::GAME_GLOBALS.pointsTeamB += 1;
        }
        if (pos.y + (glm::vec4(radius) * model).x > 300 && velocity.y > 0) {
            velocity.y *= -1;
        }
        if (pos.y - (glm::vec4(radius) * model).x < -300 && velocity.y < 0) {
            velocity.y *= -1;
        }
        velocity = glm::normalize(velocity);

        this->pos += velocity * (MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);

        view = camera->getViewMatrix();
        projection = camera->getProjection();
    }

    void Ball::render()
    {
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
            1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
            1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"),
            1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size() / 3));
        glBindVertexArray(0);
    }

    void Ball::shutdown()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

}