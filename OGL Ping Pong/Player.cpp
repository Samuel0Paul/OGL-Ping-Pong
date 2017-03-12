#include "stdafx.h"
#include "Player.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"

#define BLOCK_BB_EXTRA 5

namespace game
{

    Player::Player(objects::Block *block, objects::Ball *ball) :
        block(block),
        ball(ball)
    {
    }

    Player::~Player()
    {
    }

    void Player::update(double time)
    {
        block->update(time);
        ball->update(time);
    }

    void Player::shutdown()
    {
    }

    PlayerRight::PlayerRight(objects::Block *block, objects::Ball *ball) :
        Player(block, ball)
    {
    }

    PlayerRight::~PlayerRight()
    {
    }

    void PlayerRight::update(double time)
    {
        if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_UP) == GLFW_PRESS) {
            if (block->pos.y + block->getHeight() / 2 < 600 / 2) {
                block->pos.y += 
                    (block->MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
            }
        }
        if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
            if (block->pos.y - block->getHeight() / 2 > - 600 / 2) {
                block->pos.y -= (block->MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
            }
        }

        ball_xp = ball->pos.x + ball->getRadius();
        ball_xn = ball->pos.x - ball->getRadius();
        ball_yp = ball->pos.y + ball->getRadius();
        ball_yn = ball->pos.y - ball->getRadius();
        block_xp = block->pos.x + block->getWidth() / 2 + BLOCK_BB_EXTRA;
        block_xn = block->pos.x - block->getWidth() / 2 - BLOCK_BB_EXTRA;
        block_yp = block->pos.y + block->getHeight() / 2 + BLOCK_BB_EXTRA;
        block_yn = block->pos.y - block->getHeight() / 2 - BLOCK_BB_EXTRA;

        std::clog << "\n\right: "
            << "\nball_xp: " << ball_xp
            << "\nball_xn: " << ball_xn
            << "\nball_yp: " << ball_yp
            << "\nball_yn: " << ball_yn
            << "\nblock_xp: " << block_xp
            << "\nblock_xn: " << block_xn
            << "\nblock_yp: " << block_yp
            << "\nblock_yn: " << block_yn
            << std::endl;
        std::clog << "\nvel: " << glm::to_string(ball->velocity) << std::endl;

        if ((ball_xp > block_xn && ball_xp < block_xp) && (ball_yp < block_yp && ball_yn > block_yn))
        {
            auto &delta = tmp[0];
            delta = (ball->pos.y - block->pos.y) / (block->getHeight() / 2);
            glm::vec3 normal = glm::normalize(glm::vec3(-1.f, delta, 0.f));

            std::clog << "\ndelta: " << delta
                << "\nnormal: " << glm::to_string(normal) << std::endl;

            if (ball->velocity.x > 0)
            {
                ball->velocity = glm::reflect(ball->velocity, normal);
            }
        }

        ball->velocity = glm::normalize(ball->velocity);

        Player::update(time);
    }

    void PlayerRight::shutdown()
    {
    }

    PlayerLeft::PlayerLeft(objects::Block *block, objects::Ball *ball) :
        Player(block, ball)
    {
    }

    PlayerLeft::~PlayerLeft()
    {
    }

    void PlayerLeft::update(double time)
    {
        if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_T) == GLFW_PRESS) {
            if (block->pos.y + block->getHeight() / 2 < 600 / 2) {
                block->pos.y += 
                    (block->MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
            }
        }
        if (glfwGetKey(mylib::GLOBAL_VARS.activeGLFWwindow, GLFW_KEY_G) == GLFW_PRESS) {
            if (block->pos.y - block->getHeight() / 2 > - 600 / 2) {
                block->pos.y -= (block->MOVE_SPEED * static_cast<float>(mylib::GLOBAL_VARS.getTimeOffset()) * 100);
            }
        }
        ball_xp = ball->pos.x + ball->getRadius();
        ball_xn = ball->pos.x - ball->getRadius();
        ball_yp = ball->pos.y + ball->getRadius();
        ball_yn = ball->pos.y - ball->getRadius();
        block_xp = block->pos.x + block->getWidth() / 2 + BLOCK_BB_EXTRA;
        block_xn = block->pos.x - block->getWidth() / 2 - BLOCK_BB_EXTRA;
        block_yp = block->pos.y + block->getHeight() / 2 + BLOCK_BB_EXTRA;
        block_yn = block->pos.y - block->getHeight() / 2 - BLOCK_BB_EXTRA;

        std::clog << "\n\nleft: "
            << "\nball_xp: " << ball_xp
            << "\nball_xn: " << ball_xn
            << "\nball_yp: " << ball_yp
            << "\nball_yn: " << ball_yn
            << "\nblock_xp: " << block_xp
            << "\nblock_xn: " << block_xn
            << "\nblock_yp: " << block_yp
            << "\nblock_yn: " << block_yn
            << std::endl;
        std::clog << "\nvel: " << glm::to_string(ball->velocity) << std::endl;

        //auto &delta = tmp[0];
        //delta = (ball->pos.y - block->pos.y) / (block->getHeight() / 2);
        //
        //// ball hitting the "front side" and in the bounds of the front side
        //// Zone B:
        //if ((ball_xn < block_xp && ball_xn > block_xn) && (ball_yp < block_yp && ball_yn > block_yn))
        //{
        //    // zone 1 - 
        //    if (ball->pos.y > block->pos.y) {
        //        ball->velocity *= -1;
        //        ball->velocity.y += delta * ball->velocity.y;
        //        ball->velocity.x += (1 - delta) * ball->velocity.x;
        //    }
        //    // zone 2 - 
        //    if (ball->pos.y < block->pos.y) {
        //        ball->velocity *= -1;
        //        ball->velocity.y -= (-delta) * ball->velocity.y;
        //        ball->velocity.x -= (1 - (-delta)) * ball->velocity.x;
        //    }
        //}
        //
        //ball->velocity = glm::normalize(ball->velocity);

        // ball hitting the "front side" and in the bounds of the front side
        // Zone B:
        if ((ball_xn < block_xp && ball_xn > block_xn) && (ball_yp < block_yp && ball_yn > block_yn))
        {
            auto &delta = tmp[0];
            delta = (ball->pos.y - block->pos.y) / (block->getHeight() / 2);
            glm::vec3 normal = glm::normalize(glm::vec3(1.f, delta, 0.f));

            std::clog << "\ndelta: " << delta
                << "\nnormal: " << glm::to_string(normal) << std::endl;

            if (ball->velocity.x < 0) {
                ball->velocity = glm::reflect(ball->velocity, normal);
            }
        }

        ball->velocity = glm::normalize(ball->velocity);

        Player::update(time);
    }

    void PlayerLeft::shutdown()
    {
    }

}