#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"

#include "Player.h"

namespace game
{
    class PlayerRunner
    {
    public:
        std::vector<Player*> vPlayers;

        PlayerRunner() = default;
        PlayerRunner(std::vector<Player*>);
        virtual ~PlayerRunner();

        virtual void update(double time);
        virtual void render();
    };

}
