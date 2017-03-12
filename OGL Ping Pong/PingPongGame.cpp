#include "stdafx.h"
#include "PingPongGame.h"

#include "PlayerRunner.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include <algorithm>

#define TEST

game::GameGlobalVars game::GAME_GLOBALS = { 0, 0 };

typedef void (APIENTRY *GLDEBUGPROC)(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar *message, const void *userParam);

void APIENTRY DebugMessageCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar *message, const void *userParam)
{
    std::cout << "src: " << source
        << "\ntype: " << type
        << "\nid: " << id
        << "\nlength: " << length
        << "msg: " << message;
}

game::PingPongGame::PingPongGame(mylib::Window && window) :
    mylib::App(std::move(window))
{
    constexpr float radius = 0.2f;
    const int n = 64;
    float x, y;
    ball_vertices.push_back(0);
    ball_vertices.push_back(0);
    ball_vertices.push_back(0);
    ball_vertices.push_back(radius);
    ball_vertices.push_back(0);
    ball_vertices.push_back(0);
    for (int i = 0; i < n; ++i) {
        float ang = static_cast<float>(M_PI) * 2.0f / n * i;
        x = glm::cos(ang) * radius;
        y = -glm::sin(ang) * radius;

        ball_vertices.push_back(x);
        ball_vertices.push_back(y);
        ball_vertices.push_back(0);
    }
    ball_vertices.push_back(radius);
    ball_vertices.push_back(0);
    ball_vertices.push_back(0);
}

game::PingPongGame::~PingPongGame()
{
    std::cout << "Team A: " << GAME_GLOBALS.pointsTeamA
        << "\nTeam B: " << GAME_GLOBALS.pointsTeamB;
    if (GAME_GLOBALS.pointsTeamA != GAME_GLOBALS.pointsTeamB)
        std::cout << "\n\nWinner: " << (GAME_GLOBALS.pointsTeamA > GAME_GLOBALS.pointsTeamB ? "Team A" : "Team B")
        << std::endl;
    else
        std::cout << "\n\nIt's a Draw. Good game though..." << std::endl;
}

void game::PingPongGame::startup()
{
    glDebugMessageCallback(DebugMessageCallback, nullptr);

#ifndef TEST
    blockShader = mylib::Shader({
std::make_pair(
    "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/block/block.vert",
    GL_VERTEX_SHADER),
std::make_pair(
    "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/block/block.frag",
    GL_FRAGMENT_SHADER)
    });
    ballShader = mylib::Shader({
        std::make_pair(
            "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/ball/ball.vert",
            GL_VERTEX_SHADER),
        std::make_pair(
            "c:/Users/samuel vishesh paul/documents/visual studio 2015/Projects/OGL Ping Pong/OGL Ping Pong/shaders/ping pong/ball/ball.frag",
            GL_FRAGMENT_SHADER)
    });

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    // block data
    glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
    glBufferData(GL_ARRAY_BUFFER,
        block_vertices.size() * sizeof(*(block_vertices.data())),
        block_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        block_indices.size() * sizeof(*(block_indices.data())),
        block_indices.data(), GL_STATIC_DRAW);
    // ball data
    glBindBuffer(GL_ARRAY_BUFFER, ball_VBO);
    glBufferData(GL_ARRAY_BUFFER,
        ball_vertices.size() * sizeof(*(ball_vertices.data())),
        ball_vertices.data(), GL_STATIC_DRAW);

    GLint positionAttribLoc{ 0 }, colorAttribLoc{ 0 };
    // block attr
    glBindVertexArray(block_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block_EBO);
    positionAttribLoc = glGetAttribLocation(blockShader.program, "position");
    glEnableVertexAttribArray(positionAttribLoc);
    glVertexAttribPointer(positionAttribLoc, 3,
        GL_FLOAT, GL_FALSE,
        3 * sizeof(*(block_vertices.data())), ML_BUFFER_OFFSET(0));
    glBindVertexArray(0);
    // ball attr
    glBindVertexArray(ball_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, ball_VBO);
    positionAttribLoc = glGetAttribLocation(ballShader.program, "position");
    glEnableVertexAttribArray(positionAttribLoc);
    glVertexAttribPointer(positionAttribLoc, 3,
        GL_FLOAT, GL_FALSE,
        3 * sizeof(*(ball_vertices.data())), ML_BUFFER_OFFSET(0));
    glBindVertexArray(0);

    camera = mylib::Camera(
        window.width, window.height,
        glm::vec3(0.0f, 0.0f, 3.0f),	// cameraPos
        glm::vec3(0.0f, 1.0f, 0.0f));	// cmaeraUp
    orthoCam = mylib::OrthoCamera(camera);
    cameraController = mylib::CameraController(
        &orthoCam, &window);

    cam = &orthoCam;
#endif // !TEST

    camera = mylib::Camera(
        window.width, window.height,
        glm::vec3(0.0f, 0.0f, 3.0f),	// cameraPos
        glm::vec3(0.0f, 1.0f, 0.0f));	// cmaeraUp
    orthoCam = mylib::OrthoCamera(camera);
    cameraController = mylib::CameraController(
        &orthoCam, &window);

    cam = &orthoCam;
    mylib::GLOBAL_VARS.camera = cam;

    blockRight = game::objects::Block(glm::vec3(350.f, 0.f, 0.f), cam);
    blockLeft = game::objects::Block(glm::vec3(-350.f, 0.f, 0.f), cam);
    ballOne = game::objects::Ball(glm::vec3(0), 0.2f, 64);

    playerA = new game::PlayerRight(&blockRight, &ballOne);
    playerB = new game::PlayerLeft(&blockLeft, &ballOne);
    playerRunner = game::PlayerRunner({ playerA, playerB });
}

void game::PingPongGame::update(double time)
{
#ifndef TEST
    cameraController.update(cameraController, time);
    view = cam->getViewMatrix();
    projection = cam->getProjection();

    activeShader = &blockShader;
    activeShader->use();
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "projection"),
        1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "view"),
        1, GL_FALSE, glm::value_ptr(view));

    activeShader = &ballShader;
    activeShader->use();
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "projection"),
        1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "view"),
        1, GL_FALSE, glm::value_ptr(view));
#endif // !TEST

    mylib::GLOBAL_VARS.updateTime();
    //blockRight.update(time);
    //blockLeft.update(time);
    //ballOne.update(time);
    playerRunner.update(time);

}

void game::PingPongGame::render()
{
#ifndef TEST
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    activeShader = &blockShader;
    activeShader->use();
    glBindVertexArray(block_VAO);
    model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "model"),
        1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ML_BUFFER_OFFSET(0));
    glBindVertexArray(0);

    activeShader = &ballShader;
    activeShader->use();
    glBindVertexArray(ball_VAO);
    model = glm::translate(glm::mat4(), glm::vec3(-40.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(300));
    glUniformMatrix4fv(glGetUniformLocation(activeShader->program, "model"),
        1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLE_FAN, 0, ball_vertices.size() / 3);
    glBindVertexArray(0);
#endif // !TEST

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //ballOne.render();
    //blockRight.render();
    //blockLeft.render();
    playerRunner.render();

}

void game::PingPongGame::shutdown()
{
#ifndef TEST
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
#endif // !TEST

    delete this->playerA;
    delete this->playerB;
}
