#ifndef Minesweeper_hpp
#define Minesweeper_hpp

#include <SDL2/SDL.h>


class Minesweeper 
{
    // Types
    public:
        static const int ROWS = 50;    /* const int for num rows              */
        static const int COLS = 25;    /* const int for num columns           */
    
    protected:
    private:

    // API 
    public:
        Minesweeper(SDL_Renderer* renderer);
        ~Minesweeper();
        bool init(int board_width, int board_height);
        void render();
        void handleKey(SDL_Keycode& key_code);
        void handleMouse(SDL_MouseButtonEvent& click);
        void handleMouse(SDL_MouseMotionEvent& move);

    protected:

    private:

    // Modules
    private:
        SDL_Renderer* m_renderer;   /* Pointer to the renderer for the Game     */
        SDL_Rect** m_board;        /* SDL_Rect 2D array representing the Minesweeper board */
        int m_cell_width;
        int m_cell_height;
};

#endif /* Minesweeper_hpp */