#include "Minesweeper.hpp"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <ctime>

/**
 * @brief Construct a new Minesweeper::Minesweeper object
 * 
 * @param renderer - SDL_Renderer used by the game
 */
Minesweeper::Minesweeper() : m_title("Minesweeper")
{
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
    SDL_DestroyTexture(m_cell_good_flag_texture);
    SDL_DestroyTexture(m_cell_bad_flag_texture);
    SDL_DestroyTexture(m_cell_bomb_texture);
    SDL_DestroyTexture(m_cell_boom_texture);
}


/**
 * @brief initializes Minesweeper
 * 
 * @param board_width 
 * @param board_height 
 * @return true if initialized successfully
 */
bool Minesweeper::initPostHook()
{
    srand ( time(NULL) );
    initTextures();
    m_border_cell.proximity = -1;
    m_border_cell.is_bomb = false;
    m_border_cell.snooped = true;
    m_moves = 0;

    int max_px = std::max(m_screen_width, m_screen_height);
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


/**
 * @brief inititialize textures
 * TODO: fallback when failure
 * 
 */
void Minesweeper::initTextures()
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
    SDL_Surface * cell_good_flag_surface = IMG_Load("./Minesweeper/assets/goodflag.png");
    SDL_Surface * cell_bad_flag_surface = IMG_Load("./Minesweeper/assets/badflag.png");
    SDL_Surface * cell_bomb_surface = IMG_Load("./Minesweeper/assets/bomb.png");
    SDL_Surface * cell_boom_surface = IMG_Load("./Minesweeper/assets/boom.png");
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
    m_cell_good_flag_texture = SDL_CreateTextureFromSurface(m_renderer, cell_good_flag_surface);
    m_cell_bad_flag_texture = SDL_CreateTextureFromSurface(m_renderer, cell_bad_flag_surface);
    m_cell_bomb_texture = SDL_CreateTextureFromSurface(m_renderer, cell_bomb_surface);
    m_cell_boom_texture = SDL_CreateTextureFromSurface(m_renderer, cell_boom_surface);
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
    SDL_FreeSurface(cell_good_flag_surface);
    SDL_FreeSurface(cell_bad_flag_surface);
    SDL_FreeSurface(cell_bomb_surface);
    SDL_FreeSurface(cell_boom_surface);
    
}


/**
 * @brief Initializes Cells for the Game
 * 
 * @return true if successfully initialized
 */
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
    //TODO: return false on failure
    return true;
}


/**
 * @brief Populates cell fields
 * 
 * @param cell  - cell to populate
 * @param x     - cell's x pos on board
 * @param y     - cell's y pos on board
 */
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


/**
 * @brief initializes neighbours of each cell. 
 * Used for bfs
 * 
 */
void Minesweeper::initCellNeighbours()
{
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


/**
 * @brief adds neighbours to the cell
 * 
 * @param cell          - cell to add neighbours to
 * @param left          - cell to the left of the cell being added to
 * @param top_left      - cell to the top left of the cell being added to
 * @param top           - cell to the top of the cell being added to
 * @param top_right     - cell to the top right of the cell being added to
 * @param right         - cell to the right of the cell being added to
 * @param bottom_right  - cell to the bottom right of the cell being added to
 * @param bottom        - cell to the bottom of the cell being added to
 * @param bottom_left   - cell to the bottom left of the cell being added to
 */
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


/**
 * @brief Does nothing
 * 
 */
void Minesweeper::renderPreHook()
{
    return;
}


/**
 * @brief Renders the cell textures
 * 
 */
void Minesweeper::renderMidHook()
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
 * @brief Does nothing
 * 
 */
void Minesweeper::renderPostHook()
{
    // game over msg would go here
    return;
}


/**
 * @brief Handles keyboard button click
 * 
 * @param key_event - SDL_KeyboardEvent of keyboard button pressed
 */
void Minesweeper::handleKey(SDL_KeyboardEvent& key_event)
{

}


/**
 * @brief Handles mouse button click
 * 
 * @param mouse_event - SDL_MouseButtonEvent of mouse click received
 */
void Minesweeper::handleMouse(SDL_MouseButtonEvent& mouse_event)
{
    Uint8 button = mouse_event.button;
    int row = mouse_event.x/m_cell_width;
    int col = mouse_event.y/m_cell_height;
    Cell &cell = m_cells.at(col).at(row);
    if(button == SDL_BUTTON_LEFT)
    {
        handleSelection(cell);
    }
    else
    {
        handleFlag(cell);
    }
}


/**
 * @brief handle cell selection. starts bfs and increments move counter
 * 
 * @param cell - cell that was selected
 */
void Minesweeper::handleSelection(Cell &cell)
{
    if(m_moves == 0)
    {
        initBombs(cell);
    }
    m_moves++;
    printf("Cell ( %d, %d ): bomb: %s\n", cell.x, cell.y, cell.is_bomb ? "true" : "false");
    if(cell.is_bomb)
    {
        gameOver(cell);
    }
    else
    {
        search(cell);
    }
    printBoard();
}


/**
 * @brief handle flag selection.
 * 
 * @param cell - cell that was flagged
 */
void Minesweeper::handleFlag(Cell &cell)
{
    if(!cell.snooped)
    {
        cell.is_flag = !cell.is_flag;
        cell.texture = cell.is_flag ? m_cell_flag_texture : m_cell_base_texture;
    }
}


/**
 * @brief initializes bombs on the board
 * 
 * @param cell - starting cell, cant be the bomb
 */
void Minesweeper::initBombs(Cell &cell)
{
    for (int i = 0; i < NUM_BOMBS; i++)
    {
        Cell & bomb_cell = m_cells.at(rand() % ROWS ).at(rand() % COLS );
        if(bomb_cell.x == cell.x && bomb_cell.y == cell.y)
        {
            i--;
            continue;
        }
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


/**
 * @brief bfs search
 * 
 * @param cell - cell that the bfs starts at
 */
void Minesweeper::search(Cell &cell)
{
    //base case
    if(cell.snooped || cell.proximity == -1)
    {
        return;
    }
    cell.snooped = true;
    applyTexture(cell);
    if(cell.proximity > 0)
    {
        return;
    }
    else
    {
        for(int i = 0; i < CELL_POS::NUM_POSITIONS; i++)
        {
            search(*cell.neighbours[i]);
        }
        return;   
    }
}


/**
 * @brief Applies a texture to the the cell to render the correct image
 * 
 * @param cell to apply the texture to
 */
void Minesweeper::applyTexture(Cell &cell)
{
    switch (cell.proximity)
    {
    case 0:
        cell.texture = m_cell_0_texture;
        break;
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
        printf("\n\n%d\n\n", cell.proximity);
        break;
    }
}


/**
 * @brief Game Over
 * 
 * @param cell - losing cell
 */
void Minesweeper::gameOver(Cell &cell)
{
    for(auto &cell_row : m_cells)
    {
        for(auto &cell : cell_row)
        {
            applyTexture(cell);
            if(cell.is_bomb && cell.is_flag)
            {
                cell.texture = m_cell_good_flag_texture;
            }
            else if(!cell.is_bomb && cell.is_flag)
            {
                cell.texture = m_cell_bad_flag_texture;
            }
            else if(cell.is_bomb)
            {
                cell.texture = m_cell_bomb_texture;
            }
        }
    }
    cell.texture = m_cell_boom_texture;
}


/**
 * @brief Prints the board onto stdout
 * 
 */
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
        }
        board += row + "\n";
    }
    board += "\n";
    printf("%s", board.c_str());
}