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
    SDL_Surface * cell_0_surface = IMG_Load("./Minesweeper/assets/cell0.png");
    SDL_Surface * cell_1_surface = IMG_Load("./Minesweeper/assets/cell1.png");
    SDL_Surface * cell_2_surface = IMG_Load("./Minesweeper/assets/cell2.png");
    SDL_Surface * cell_3_surface = IMG_Load("./Minesweeper/assets/cell3.png");
    SDL_Surface * cell_4_surface = IMG_Load("./Minesweeper/assets/cell4.png");
    SDL_Surface * cell_5_surface = IMG_Load("./Minesweeper/assets/cell5.png");
    SDL_Surface * cell_6_surface = IMG_Load("./Minesweeper/assets/cell6.png");
    SDL_Surface * cell_7_surface = IMG_Load("./Minesweeper/assets/cell7.png");
    SDL_Surface * cell_8_surface = IMG_Load("./Minesweeper/assets/cell8.png");
    SDL_Surface * cell_base_surface = IMG_Load("./Minesweeper/assets/cell_base.png");
    SDL_Surface * cell_flag_surface = IMG_Load("./Minesweeper/assets/flag.png");
    SDL_Surface * cell_bong_surface = IMG_Load("./Minesweeper/assets/bomg.png");
    m_cell_0_texture = SDL_CreateTextureFromSurface(m_renderer, cell_0_surface);
    m_cell_1_texture = SDL_CreateTextureFromSurface(m_renderer, cell_1_surface);
    m_cell_2_texture = SDL_CreateTextureFromSurface(m_renderer, cell_2_surface);
    m_cell_3_texture = SDL_CreateTextureFromSurface(m_renderer, cell_3_surface);
    m_cell_4_texture = SDL_CreateTextureFromSurface(m_renderer, cell_4_surface);
    m_cell_5_texture = SDL_CreateTextureFromSurface(m_renderer, cell_5_surface);
    m_cell_6_texture = SDL_CreateTextureFromSurface(m_renderer, cell_6_surface);
    m_cell_7_texture = SDL_CreateTextureFromSurface(m_renderer, cell_7_surface);
    m_cell_8_texture = SDL_CreateTextureFromSurface(m_renderer, cell_8_surface);
    m_cell_base_texture = SDL_CreateTextureFromSurface(m_renderer, cell_base_surface);
    m_cell_flag_texture = SDL_CreateTextureFromSurface(m_renderer, cell_flag_surface);
    m_cell_bomg_texture = SDL_CreateTextureFromSurface(m_renderer, cell_bong_surface);
    SDL_FreeSurface(cell_0_surface);
    SDL_FreeSurface(cell_1_surface);
    SDL_FreeSurface(cell_2_surface);
    SDL_FreeSurface(cell_3_surface);
    SDL_FreeSurface(cell_4_surface);
    SDL_FreeSurface(cell_5_surface);
    SDL_FreeSurface(cell_6_surface);
    SDL_FreeSurface(cell_7_surface);
    SDL_FreeSurface(cell_8_surface);
    SDL_FreeSurface(cell_base_surface);
    SDL_FreeSurface(cell_flag_surface);
    SDL_FreeSurface(cell_bong_surface);
    m_null_cell.x = -1;
    m_null_cell.y = -1;
    m_null_cell.snooped = true;
}

/**
 * @brief Destroy the Minesweeper::Minesweeper object
 * 
 */
Minesweeper::~Minesweeper()
{
    SDL_DestroyTexture(m_cell_0_texture);
    SDL_DestroyTexture(m_cell_1_texture);
    SDL_DestroyTexture(m_cell_2_texture);
    SDL_DestroyTexture(m_cell_3_texture);
    SDL_DestroyTexture(m_cell_4_texture);
    SDL_DestroyTexture(m_cell_5_texture);
    SDL_DestroyTexture(m_cell_6_texture);
    SDL_DestroyTexture(m_cell_7_texture);
    SDL_DestroyTexture(m_cell_8_texture);
    SDL_DestroyTexture(m_cell_base_texture);
    SDL_DestroyTexture(m_cell_flag_texture);
    SDL_DestroyTexture(m_cell_bomg_texture);
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
    for(int board_y = 0; board_y < ROWS; board_y++)
    {
        std::vector<Cell> cell_row;
        for(int board_x = 0; board_x < COLS; board_x++)
        {
            Cell cell;
            populateCell(cell, board_x, board_y);
            cell_row.emplace_back(std::move(cell));
        }
        m_cells.emplace_back(std::move(cell_row));
    }
    return true;
}

void Minesweeper::populateCell(Cell& cell, int x, int y)
{
    cell.x = x;
    cell.y = y;
    cell.rect.y = y * m_cell_height;
    cell.rect.x = x * m_cell_width;
    cell.rect.w = m_cell_width;
    cell.rect.h = m_cell_height;
    cell.snooped = false;
    cell.proximity = 0;
    cell.texture = m_cell_base_texture;
    initCellNeighbours(cell);
}


void Minesweeper::initCellNeighbours(Cell& cell)
{
    //left border
    if (cell.x == 0)
    {
        cell.neighbours[CELL_POS::TOP_LEFT] = &m_null_cell;
        cell.neighbours[CELL_POS::LEFT] = &m_null_cell;
        cell.neighbours[CELL_POS::BOTTOM_LEFT] = &m_null_cell;
        cell.neighbours[CELL_POS::RIGHT] = &m_cells.at(cell.x+1).at(cell.y);
        // top left
        if (cell.y == 0)
        {
            // cell.neighbours.at( CELL_POS::TOP ) = &m_null_cell;
            // cell.neighbours.at( CELL_POS::TOP_RIGHT ) = &m_null_cell;
            // cell.neighbours.at( CELL_POS::BOTTOM_RIGHT ) = &m_cells.at(cell.x+1).at(cell.y+1);
            // cell.neighbours.at( CELL_POS::BOTTOM ) = &m_cells.at(cell.x).at(cell.y+1);
        }
        //bottom left
        else if (cell.y == ROWS)
        {
            // cell.neighbours.at( CELL_POS::TOP ) = &m_cells.at(cell.x).at(cell.y-1); 
            // cell.neighbours.at( CELL_POS::TOP_RIGHT ) = &m_cells.at(cell.x+1).at(cell l.y-1);
            // cell.neighbours.at( CELL_POS::BOTTOM_RIGHT ) = &m_null_cell;
            // cell.neighbours.at( CELL_POS::BOTTOM ) = &m_null_cell;
        }
        //left
        else
        {
            // cell.neighbours.at( CELL_POS::TOP ) = &m_cells.at(cell.x).at(cell.y-1);
            // cell.neighbours.at( CELL_POS::TOP_RIGHT ) = &m_cells.at(cell.x+1).at(cell.y-1);
            // cell.neighbours.at( CELL_POS::BOTTOM_RIGHT ) = &m_cells.at(cell.x+1).at(cell.y+1);
            // cell.neighbours.at( CELL_POS::BOTTOM ) = &m_cells.at(cell.x).at(cell.y+1);

        }

    }
    else if(cell.x == COLS)
    {
        // cell.neighbours.at( CELL_POS::LEFT ) = m_cells.at(col).at(row);
    }

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
    Cell &cell = m_cells.at(col).at(row);
    printf("Cell ( %d, %d ): snooped: %d\n", cell.x, cell.y, cell.snooped);
    cell.snooped = true;
    cell.texture = m_cell_0_texture;

}
