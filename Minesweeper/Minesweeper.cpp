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
    printBoard(); // print to console for development
    return true;
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
    initCellNeighbours();
    initBombs();
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
    cell.is_bomb = false;
    cell.proximity = 0;
    cell.texture = m_cell_base_texture;
}


void Minesweeper::initCellNeighbours()
{
    m_border_cell.proximity = -1;
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            Cell &cell = m_cells.at(y).at(x);
            
            //corner conditions
            //top-left
            if ( ( x == 0 ) && ( y == 0 ))
            {
                Cell &right = m_cells.at(y).at(x+1);
                Cell &bottom = m_cells.at(y+1).at(x);
                Cell &bottom_right = m_cells.at(y+1).at(x+1);
                addNeighbours(cell, m_border_cell, m_border_cell, m_border_cell, m_border_cell, right, bottom_right, bottom, m_border_cell);
                right.neighbours[CELL_POS::LEFT] = &cell;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &cell;
                bottom.neighbours[CELL_POS::TOP] = &cell;
            }
            //top-right
            else if ( ( x == (COLS-1) ) && ( y == 0 ))
            {
                Cell &left = m_cells.at(y).at(x-1);
                Cell &bottom = m_cells.at(y+1).at(x);
                Cell &bottom_left = m_cells.at(y+1).at(x-1);
                addNeighbours(cell, left, m_border_cell, m_border_cell, m_border_cell, m_border_cell, m_border_cell, bottom, bottom_left);
                bottom.neighbours[CELL_POS::TOP] = &cell;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &cell;
                left.neighbours[CELL_POS::RIGHT] = &cell;
            }
            //bottom-right
            else if ( ( x == (COLS-1) ) && ( y == (ROWS-1) ))
            {
                Cell &top = m_cells.at(y-1).at(x);
                Cell &left = m_cells.at(y).at(x-1);
                Cell &top_left = m_cells.at(y-1).at(x-1);
                addNeighbours(cell, left, top_left, top, m_border_cell, m_border_cell, m_border_cell, m_border_cell, m_border_cell);
                left.neighbours[CELL_POS::RIGHT] = &cell;
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &cell;
            }
            //bottom-left
            else if ( ( x == 0 ) && ( y == (ROWS-1) ))
            {
                Cell &right = m_cells.at(y).at(x+1);
                Cell &top = m_cells.at(y-1).at(x);
                Cell &top_right = m_cells.at(y-1).at(x+1);
                addNeighbours(cell, m_border_cell, m_border_cell, top, top_right, right, m_border_cell, m_border_cell, m_border_cell);
                right.neighbours[CELL_POS::LEFT] = &cell;
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &cell;
            }
            //border conditions
            //left border
            else if (x == 0)
            {
                Cell &top = m_cells.at(y-1).at(x);
                Cell &top_right = m_cells.at(y-1).at(x+1);
                Cell &right = m_cells.at(y).at(x+1);
                Cell &bottom_right = m_cells.at(y+1).at(x+1);
                Cell &bottom = m_cells.at(y+1).at(x);
                addNeighbours(cell, m_border_cell, m_border_cell, top, top_right, right, bottom_right, bottom, m_border_cell);
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &cell;
                right.neighbours[CELL_POS::LEFT] = &cell;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &cell;
                bottom.neighbours[CELL_POS::TOP] = &cell;
            }
            //top border
            else if (y == 0)
            {
                Cell &left = m_cells.at(y).at(x-1);
                Cell &right = m_cells.at(y).at(x+1);
                Cell &bottom_right = m_cells.at(y+1).at(x+1);
                Cell &bottom = m_cells.at(y+1).at(x);
                Cell &bottom_left = m_cells.at(y+1).at(x-1);
                addNeighbours(cell, left, m_border_cell, m_border_cell, m_border_cell, right, bottom_right, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &cell;
                right.neighbours[CELL_POS::LEFT] = &cell;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &cell;
                bottom.neighbours[CELL_POS::TOP] = &cell;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &cell;
            }
            //right border
            else if (x == (COLS-1))
            {
                Cell &left = m_cells.at(y).at(x-1);
                Cell &top_left = m_cells.at(y-1).at(x-1);
                Cell &top = m_cells.at(y-1).at(x);
                Cell &bottom = m_cells.at(y+1).at(x);
                Cell &bottom_left = m_cells.at(y+1).at(x-1);
                addNeighbours(cell, left, top_left, top, m_border_cell, m_border_cell, m_border_cell, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &cell;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &cell;
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                bottom.neighbours[CELL_POS::TOP] = &cell;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &cell;
            }
            //bottom border
            else if (y == (ROWS-1))
            {
                Cell &left = m_cells.at(y).at(x-1);
                Cell &top_left = m_cells.at(y-1).at(x-1);
                Cell &top = m_cells.at(y-1).at(x);
                Cell &top_right = m_cells.at(y-1).at(x+1);
                Cell &right = m_cells.at(y).at(x+1);
                addNeighbours(cell, left, top_left, top, top_right, right, m_border_cell, m_border_cell, m_border_cell);
                left.neighbours[CELL_POS::RIGHT] = &cell;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &cell;
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &cell;
                right.neighbours[CELL_POS::LEFT] = &cell;
            }
            //everything else
            else
            {
                Cell &left = m_cells.at(y).at(x-1);
                Cell &top = m_cells.at(y-1).at(x);
                Cell &right = m_cells.at(y).at(x+1);
                Cell &bottom = m_cells.at(y+1).at(x);
                Cell &top_left = m_cells.at(y-1).at(x-1);
                Cell &top_right = m_cells.at(y-1).at(x+1);
                Cell &bottom_left = m_cells.at(y+1).at(x-1);
                Cell &bottom_right = m_cells.at(y+1).at(x+1);
                addNeighbours(cell, left, top_left, top, top_right, right, bottom_right, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &cell;
                top.neighbours[CELL_POS::BOTTOM] = &cell;
                right.neighbours[CELL_POS::LEFT] = &cell;
                bottom.neighbours[CELL_POS::TOP] = &cell;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &cell;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &cell;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &cell;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &cell;
            }
        }
    }
}


void Minesweeper::addNeighbours(Cell& cell, Cell& left, Cell& top_left, Cell& top, Cell& top_right, Cell& right, Cell& bottom_right, Cell& bottom, Cell& bottom_left)
{
    cell.neighbours[CELL_POS::LEFT] = &left;
    cell.neighbours[CELL_POS::TOP_LEFT] = &top_left;
    cell.neighbours[CELL_POS::TOP] = &top;
    cell.neighbours[CELL_POS::TOP_RIGHT] = &top_right;
    cell.neighbours[CELL_POS::RIGHT] = &right;
    cell.neighbours[CELL_POS::BOTTOM_RIGHT] = &bottom_right;
    cell.neighbours[CELL_POS::BOTTOM] = &bottom;
    cell.neighbours[CELL_POS::BOTTOM_LEFT] = &bottom_left;
}

void Minesweeper::search(int x_i, int y_i, bool stop = false)
{
    //base case
    if(stop)
    {
        return;
    }
    m_cells.at(y_i).at(x_i).snooped = true;
    search(x_i, y_i, visitNeighbours(m_cells.at(y_i).at(x_i)));
}

bool Minesweeper::visitNeighbours(Cell &cell)
{
    if (cell.snooped)
    {
        return true;
    }
    else
    {
        cell.snooped = true;
        printf("\n\n%d\n\n", cell.proximity);
        switch (cell.proximity)
        {
        case 1:
            cell.texture = m_cell_1_texture;
            break;

        case 2:
            cell.texture = m_cell_2_texture;
            break;

        case 3:
            cell.texture = m_cell_3_texture;
            break;

        case 4:
            cell.texture = m_cell_4_texture;
            break;

        case 5:
            cell.texture = m_cell_5_texture;
            break;

        case 6:
            cell.texture = m_cell_6_texture;
            break;

        case 7:
            cell.texture = m_cell_7_texture;
            break;

        case 8:
            cell.texture = m_cell_8_texture;
            break;
        
        default:
            cell.texture = m_cell_0_texture;
            break;
        }

        for (int i = 0; i < cell.neighbours.size(); i++)
        {
            if (cell.neighbours.at(i)->proximity == -1)
            {
                continue;
            }
            search(cell.x, cell.y, false);
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
    handleSelection(cell);
}


void Minesweeper::handleSelection(Cell &cell)
{
    printf("Cell ( %d, %d ): bomb: %s\n", cell.x, cell.y, cell.is_bomb ? "true" : "false");
    search(cell.x, cell.y);
    printBoard();
}

void Minesweeper::initBombs()
{
    for (int i = 0; i < NUM_BOMBS; i++)
    {
        Cell & bomb_cell = m_cells.at(rand() % ROWS ).at(rand() % COLS );
        bomb_cell.is_bomb = true;
    }
    for(auto &cell_row : m_cells)
    {
        for(auto &cell : cell_row)
        {
            for(auto &neighbours : cell.neighbours)
            {
                if(neighbours->is_bomb)
                {
                    cell.proximity++;
                }
            }
        }
    }
}


void Minesweeper::printBoard()
{
    std::string board = "\n";
    for (int y = 0; y < ROWS; y++)
    {
        std::string row;
        for (int x = 0; x < COLS; x++)
        {
            Cell& cell = m_cells.at(y).at(x);

            std::string val = cell.is_bomb ? "[x]" : "[" + std::to_string(cell.proximity) + "]";
            row += val;
            // row += m_cells.at(y).at(x).snooped ? val : "[ ]";
        }
        board += row + "\n";
    }
    board += "\n";
    printf("%s", board.c_str());
}