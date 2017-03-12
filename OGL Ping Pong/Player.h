#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"
#include "Ball.h"
#include "Block.h"

namespace game
{
    class Player
    {
    public:
        objects::Block *block;
        objects::Ball *ball;

        Player() = default;
        Player(objects::Block*, objects::Ball*);
        virtual ~Player();

        virtual void update(double time);
        virtual void shutdown();

    protected:
        float ball_xp;
        float ball_xn; 
        float ball_yp; 
        float ball_yn; 
        float block_xp;
        float block_xn;
        float block_yp;
        float block_yn;

        float tmp[5];
    };

    class PlayerRight :
        public Player
    {
    public:
        PlayerRight() = default;
        PlayerRight(objects::Block*, objects::Ball*);
        virtual ~PlayerRight();

        virtual void update(double time) override;
        virtual void shutdown();
    };

    class PlayerLeft :
        public Player
    {
    public:
        PlayerLeft() = default;
        PlayerLeft(objects::Block*, objects::Ball*);
        virtual ~PlayerLeft();

        virtual void update(double time) override;
        virtual void shutdown();
    };

}
