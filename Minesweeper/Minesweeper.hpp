#ifndef Minesweeper_hpp
#define Minesweeper_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <array>
#include "../Game.hpp"

class Minesweeper : public Game 
{
    // Types
    public:
        enum CELL_POS { LEFT, TOP_LEFT, TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT , NUM_POSITIONS};
        static const int ROWS = 10;         /* const int for num rows    */
        static const int COLS = 10;         /* const int for num columns */
        static const int NUM_BOMBS = 15;    /* const int for num bombs   */
        static const int THREAT_LEVEL_MIDNIGHT = 9;    /* const int proximity as bomb */
        static const int FLAG = 10;    /* const int for num bombs   */
        
        struct Cell
        {
            SDL_Texture* texture;           /* Texture for displaying the cell */
            SDL_Rect rect;                  /* Rect for rendering the texture */
            int x;                          /* int for x position   */
            int y;                          /* int for y position   */
            int proximity;                  /* int for proximity    */
            bool snooped;                   /* bool for if the Cell has been visited  */
            bool is_bomb;                   /* bool for if the Cell is a bomb */
            bool is_flag;                   /* bool for if the Cell is flagged */
            std::array<Cell *, CELL_POS::NUM_POSITIONS> neighbours;   /* Cell vector array for adjaent neighbours */
        };  /* Struct for a Cell */
    
    protected:
    private:

    // API 
    public:
        Minesweeper();
        ~Minesweeper();

        std::vector<Cell *> getNeighbours(Cell &neighbour);
        int getThreatLevel();
        void printBoard();

    protected:
        bool initPostHook() override;
        void renderPreHook() override;
        void renderMidHook() override;
        void renderPostHook() override;
        void handleKey(SDL_KeyboardEvent& key_event) override;
        void handleMouse(SDL_MouseButtonEvent& mouse_event) override;
        void handleMouse(SDL_MouseMotionEvent& mouse_motion) override;

    private:
        void initTextures();
        bool initCells();
        void populateCell(Cell& cell, int x, int y);
        void initCellNeighbours();
        void initBombs(Cell &cell);
        void search(Cell &cell);
        void addNeighbours(Cell& cell, Cell& left, Cell& top_left, Cell& top, Cell& top_right, Cell& right, Cell& bottom_right, Cell& bottom, Cell& bottom_left);
        void handleSelection(Cell &cell);
        void handleFlag(Cell &cell);
        void applyTexture(Cell &cell);
        void gameOver(Cell &cell);

    // Modules
    public:
        const char * m_title;  /* Char array for the game's title */

    private:
        std::vector<std::vector<Cell>> m_cells; /* 2D vector array of cells */
        int m_cell_width;  /* int for Cell width    */
        int m_cell_height; /* int for Cell height   */
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
        SDL_Texture * m_cell_good_flag_texture;
        SDL_Texture * m_cell_bad_flag_texture;
        SDL_Texture * m_cell_boom_texture;
        SDL_Texture * m_cell_bomb_texture;
        int m_moves;
        Cell m_border_cell;
};

#endif /* Minesweeper_hpp */