#ifndef Minesweeper_hpp
#define Minesweeper_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <array>

class Minesweeper 
{
    // Types
    public:
        enum CELL_POS { LEFT, TOP_LEFT, TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT , NUM_POSITIONS};
        static const int ROWS = 10;         /* const int for num rows    */
        static const int COLS = 10;         /* const int for num columns */
        static const int NUM_BOMBS = 40;    /* const int for num bombs   */
        
        struct Cell
        {
            SDL_Texture* texture;           /* Texture for displaying the cell */
            SDL_Rect rect;                  /* Rect for rendering the texture */
            int x;                          /* int for x position   */
            int y;                          /* int for y position   */
            int proximity;                  /* int for proximity    */
            std::array<Cell *, CELL_POS::NUM_POSITIONS> neighbours;   /* Cell vector array for adjaent neighbours */
            bool snooped;                   /* bool for if the Cell has been visited  */
            bool is_bomb;                   /* bool for if the Cell is a bomb */
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

        std::vector<Cell *> getNeighbours(Cell &neighbour);
        int getThreatLevel();
        void printBoard();

    protected:

    private:
        bool initCells();
        void populateCell(Cell& cell, int x, int y);
        void initCellNeighbours();
        void initBombs();
        void search(int x_i, int y_i, int val);
        void visitNeighbours(Cell &cell, int val);
        void addNeighbours(Cell& cell, Cell& left, Cell& top_left, Cell& top, Cell& top_right, Cell& right, Cell& bottom_right, Cell& bottom, Cell& bottom_left);

    // Modules
    private:
        SDL_Renderer* m_renderer;    /* Pointer to the renderer for the Game */
        Cell m_null_cell; 
        std::vector<std::vector<Cell>> m_cells; /* 2D vector array of cells */
        int m_cell_width;            /* int for Cell width    */
        int m_cell_height;           /* int for Cell height   */
        SDL_Texture * m_cell_0_texture; /* Texture * for cell 0 */
        SDL_Texture * m_cell_1_texture; /* Texture * for cell 1 */
        SDL_Texture * m_cell_2_texture; /* Texture * for cell 2 */
        SDL_Texture * m_cell_3_texture; /* Texture * for cell 3 */
        SDL_Texture * m_cell_4_texture; /* Texture * for cell 4 */
        SDL_Texture * m_cell_5_texture; /* Texture * for cell 5 */
        SDL_Texture * m_cell_6_texture; /* Texture * for cell 6 */
        SDL_Texture * m_cell_7_texture; /* Texture * for cell 7 */
        SDL_Texture * m_cell_8_texture; /* Texture * for cell 8 */
        SDL_Texture * m_cell_base_texture;
        SDL_Texture * m_cell_flag_texture;
        SDL_Texture * m_cell_bomg_texture;

        Cell m_border_cell;
};

#endif /* Minesweeper_hpp */