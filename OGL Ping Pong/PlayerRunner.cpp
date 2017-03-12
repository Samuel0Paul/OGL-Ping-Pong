#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "App.h"
#include "PlayerRunner.h"


namespace game
{

    PlayerRunner::PlayerRunner(std::vector<Player*> players) :
        vPlayers(players)
    {
    }

    PlayerRunner::~PlayerRunner()
    {
    }

    void PlayerRunner::update(double time)
    {
        for (Player* player : vPlayers) {
            player->block->update(time);
            player->ball->update(time);
            player->update(time);
        }
    }

    void PlayerRunner::render()
    {
        for (Player* player : vPlayers) {
            //std::clog << "block pos: " << player->block->pos.x << ", " << player->block->pos.y;
            player->block->render();
        }

        vPlayers[1]->ball->render();
    }

}