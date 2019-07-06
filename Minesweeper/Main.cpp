#include "Minesweeper.hpp"
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{
    Minesweeper* game = new Minesweeper();
    
    game->init(game->m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->SCREEN_WIDTH, game->SCREEN_HEIGHT, false);

    while( game->isRunning() )
    {
        game->update();
        SDL_Delay(1);
    }
    delete game;
    return 0;    
}