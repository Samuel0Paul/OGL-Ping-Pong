#include "stdafx.h"

#include "PingPongGame.h"

int main(const int argc, const char** const argv)
{
    {
        mylib::Window window;
        game::PingPongGame game(std::move(window));
        game.run(game);
    }

    std::cin.get();
    std::exit(EXIT_SUCCESS);
}
