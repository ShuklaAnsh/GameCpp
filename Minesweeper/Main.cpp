#include "Minesweeper.hpp"
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{
    Minesweeper* game = new Minesweeper();
    
    // game->initPreHook(ROWS, WIDTH, BOMBS); //difficulty
    game->init(game->m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

    while( game->isRunning() )
    {
        game->update();
        SDL_Delay(1);
    }
    delete game;
    return 0;    
}