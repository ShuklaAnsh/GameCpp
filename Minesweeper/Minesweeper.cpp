#include "Minesweeper.hpp"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

/**
 * @brief Construct a new Minesweeper::Minesweeper object
 * 
 * @param renderer - SDL_Renderer used by the game
 */
Minesweeper::Minesweeper(SDL_Renderer* renderer) : m_renderer(renderer)
    , m_board(nullptr)
    , m_cell_height(0)
    , m_cell_width(0)
{
}

/**
 * @brief Destroy the Minesweeper::Minesweeper object
 * 
 */
Minesweeper::~Minesweeper()
{
}


/**
 * @brief initializes Minesweeper
 * 
 * @param board_width 
 * @param board_height 
 * @return true if initialized successfully
 */
bool Minesweeper::init(int board_width, int board_height)
{
    m_cell_width = floor(board_width / COLS);
    m_cell_height = floor(board_height / ROWS);
    SDL_assert(m_cell_width > 0);   
    SDL_assert(m_cell_height > 0);   
    printf("cell width: %d, cell height: %d\n", m_cell_width, m_cell_height);
    for(int board_x = 0; board_x < COLS; board_x++)
    {
        for(int board_y = 0; board_y < ROWS; board_y ++)
        {
            printf("x: %d, y: %d\n", board_x, board_y);
        }
    }
    return false;
}


/**
 * @brief 
 * 
 */
void Minesweeper::render()
{

}


/**
 * @brief 
 * 
 * @param key_code - key code of keyboard button pressed
 */
void Minesweeper::handleKey(SDL_Keycode& key_code)
{

}


/**
 * @brief 
 * 
 * @param click - SDL_MouseButtonEvent
 */
void Minesweeper::handleMouse(SDL_MouseButtonEvent& click)
{

}


/**
 * @brief 
 * 
 * @param click - SDL_MouseMotionEvent
 */
void Minesweeper::handleMouse(SDL_MouseMotionEvent& move)
{

}
