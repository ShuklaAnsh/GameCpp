#include "Minesweeper.hpp"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

/**
 * @brief Construct a new Minesweeper::Minesweeper object
 * 
 * @param renderer - SDL_Renderer used by the game
 */
Minesweeper::Minesweeper(SDL_Renderer* renderer) : m_renderer(renderer)
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
    int max_px = std::max(board_width, board_height);
    int max_units = std::max(COLS, ROWS);
    m_cell_height = ceil(max_px / max_units);
    m_cell_width = m_cell_height;
    
    if ( (m_cell_width < 0) || (m_cell_height < 0) )
    {
        printf("cell width || height incorect.\n");
        return false;
    }  

    if ( ! initCells() )
    {
        return false;
    }

    return false;
}

bool Minesweeper::initCells()
{
    SDL_Surface * tmpSurface = IMG_Load("./Minesweeper/assets/cell.png");
    if( NULL == tmpSurface )
    {   
        printf("unable to make cell texture.");
        SDL_FreeSurface(tmpSurface);
        return false;
    }
    for(int board_y = 0; board_y < ROWS; board_y++)
    {
        std::vector<Cell> cell_row;
        for(int board_x = 0; board_x < COLS; board_x++)
        {
            Cell cell;
            populateCell(cell, board_x, board_y, tmpSurface);
            cell_row.emplace_back(std::move(cell));
        }
        m_cells.emplace_back(std::move(cell_row));
    }
    SDL_FreeSurface(tmpSurface);
    return true;
}

void Minesweeper::populateCell(Cell& cell, int x, int y, SDL_Surface * surface)
{
    cell.x = x;
    cell.y = y;
    cell.rect.y = y * m_cell_height;
    cell.rect.x = x * m_cell_width;
    cell.rect.w = m_cell_width;
    cell.rect.h = m_cell_height;
    cell.proximity = 0;
    cell.texture = SDL_CreateTextureFromSurface(m_renderer, surface);
}

/**
 * @brief 
 * 
 */
void Minesweeper::render()
{
    for (const auto& cell_row : m_cells)
    {
        for (const auto& cell : cell_row)
        {
            SDL_RenderCopy(m_renderer, cell.texture, NULL, &cell.rect);
        }
    }
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
 * @param x - Mouse x
 * 
 * @param y - Mouse y
 */
void Minesweeper::handleMouse(Sint32 x, Sint32 y)
{
    int row = x/m_cell_width;
    int col = y/m_cell_height;
    int cell_x = m_cells.at(col).at(row).x;
    int cell_y = m_cells.at(col).at(row).y;
    printf("Cell ( %d, %d )\n", cell_x, cell_y);
}
