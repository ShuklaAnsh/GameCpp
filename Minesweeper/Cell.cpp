#include "Cell.hpp"

/**
 * @brief Construct a new Cell::Cell object
 * 
 */
Cell::Cell(int params[4]) : m_value(0)
    ,m_x(0)
    ,m_y(0)
    ,m_w(0)
    ,m_h(0)
    ,m_proximity(0)
    ,m_neighbours(NULL)
{
    m_x = params[0];
    m_y = params[1];
    m_w = params[2];
    m_h = params[3];
    m_value = params[4];
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
 * @return Cell array
 */
Cell[]  Cell::getNeighbours()
{
    return m_neighbours;
}


/**
 * @brief Returns number of adjecent bombs
 * 
 */
int Cell::getDangerLevel
{
    int danger_level = 0;
    for(int i = 0; i < m_neighbours.length; i++)
    {
        if(m_neighbours[i].danger)
    }
}


/**
 * @brief Destroy the Cell::Cell object
 * 
 */
Cell::~Cell()
{
}
