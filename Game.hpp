#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
// #include "Character.hpp"
#include "Minesweeper/Minesweeper.hpp"

class Game 
{
    // Types
    public:
        //Screen dimension constants
        const int SCREEN_WIDTH = 700;
        const int SCREEN_HEIGHT = 700;
    protected:
    private:

    // API 
    public:
        Game();
        ~Game();

        bool init(const char* title, int x, int y, int height, int width, bool fullscreen);
        bool isRunning();
        void update();
        
    protected:
        void render();
        void eventHandler();

    private:

    // Modules
    protected:
        bool            m_running;         /* Boolean for if the game is running            */
        SDL_Window*     m_window;          /* Pointer to the window being rendering to      */
        SDL_Surface*    m_screen_surface;  /* Pointer to the surface the window will be on  */
        SDL_Renderer*   m_renderer;        /* Pointer to the renderer                       */
        // Character*      m_character;       /* Pointer to the Character object               */
        Minesweeper*    m_minesweeper;     /* Pointer to the Minesweeper object             */
};
#endif /* Game_hpp */