#include "Cell.hpp"

/**
 * @brief Construct a new Cell::Cell object
 * 
 */
Cell::Cell(int params[4])
{
    m_x = params[0];
    m_y = params[1];
    m_w = params[2];
    m_h = params[3];
    m_is_bomb = false;
}


/**
 * @brief 
 * 
 * @param neighbour 
 * @return true 
 * @return false 
 */
bool Cell::addNeighbour(Cell &neighbour)
{
    return false;
}

/**
 * @brief Destroy the Cell::Cell object
 * 
 */
Cell::~Cell()
{

}
