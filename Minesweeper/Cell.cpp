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
    m_is_bomb = params[4];
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
 * @brief 
 * 
 * @return Cell[8] 
 */
Cell[8] Cell::getNeighbours()
{

}


/**
 * @brief Returns number of adjecent bombs
 * 
 */
int Cell::getDangerLevel
{

}


/**
 * @brief Destroy the Cell::Cell object
 * 
 */
Cell::~Cell()
{

}
