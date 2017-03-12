#pragma once
#include "stdafx.h"
#include "App.h"
#include "Shader.h"
#include "CameraController.h"
#include "OrthoCamera.h"

#include "Block.h"
#include "Ball.h"
#include "PlayerRunner.h"

namespace game
{
    struct GameGlobalVars
    {
        long long int pointsTeamA;
        long long int pointsTeamB;
    };

    extern GameGlobalVars GAME_GLOBALS;

    class PingPongGame :
        public mylib::App
    {
    public:
        Player *playerA, *playerB;
        PlayerRunner playerRunner;
        objects::Block blockRight, blockLeft;
        objects::Ball ballOne;

        PingPongGame(mylib::Window&& window);
        ~PingPongGame();

    protected:

        void startup() override;
        void update(double) override;
        void render() override;
        void shutdown() override;

    private:
        std::vector<GLfloat> block_vertices = {
            -0.5f, -1.5f, 0.f,  // 0: LF
             0.5f, -1.5f, 0.f,  // 1: LR
             0.5f,  1.5f, 0.f,  // 2: UR
            -0.5f,  1.5f, 0.f,  // 3: UF
        };
        std::vector<GLuint> block_indices = {
            0, 1, 2,    // A
            2, 3, 0,    // B
        };

        std::vector<GLfloat> ball_vertices;

        

        GLuint VBO[5], VAO[5], EBO[5];
        GLuint &block_VBO = VBO[0], &block_VAO = VAO[0], &block_EBO = EBO[0];
        GLuint &ball_VBO = VBO[1], &ball_VAO = VAO[1];

        mylib::Shader blockShader, ballShader, *activeShader{ nullptr };
        mylib::Camera camera, *cam{ nullptr };
        mylib::OrthoCamera orthoCam;
        mylib::CameraController cameraController;
        glm::mat4 model, view, projection;
    };


}