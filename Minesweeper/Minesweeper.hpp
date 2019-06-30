#ifndef Minesweeper_hpp
#define Minesweeper_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Minesweeper 
{
    // Types
    public:
        static const int ROWS = 20;    /* const int for num rows    */
        static const int COLS = 20;    /* const int for num columns */
        static const int MIDNIGHT = 9; /* const int for Threat Level Midnight */
        struct Cell
        {
            SDL_Texture* texture;           /* Texture for displaying the cell */
            SDL_Rect rect;                  /* Rect for rendering the texture */
            int x;                          /* int for x position   */
            int y;                          /* int for y position   */
            int proximity;                  /* int for proximity    */
            std::vector<Cell *> neighbours; /* Cell array for adjaent neighbours */
        };  /* Struct for a Cell */
    
    protected:
    private:

    // API 
    public:
        Minesweeper(SDL_Renderer* renderer);
        ~Minesweeper();
        bool init(int board_width, int board_height);
        void render();
        void handleKey(SDL_Keycode& key_code);
        void handleMouse(Sint32 x, Sint32 y);

        bool addNeighbour(Cell &neighbour);
        std::vector<Cell *> getNeighbours(Cell &neighbour);
        int getThreatLevel();

    protected:

    private:
        bool initCells();
        void populateCell(Cell& cell, int x, int y, SDL_Surface * surface);
    // Modules
    private:
        SDL_Renderer* m_renderer;    /* Pointer to the renderer for the Game */
        std::vector<std::vector<Cell>> m_cells; /* 2D vector array of cells */
        int m_cell_width;            /* int for Cell width    */
        int m_cell_height;           /* int for Cell height   */
};

#endif /* Minesweeper_hpp */