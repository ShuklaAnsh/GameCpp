#ifndef Cell_hpp
#define Cell_hpp

#include <SDL2/SDL.h>


class Cell 
{
    // Types
    public:
        static const int ROWS = 50;    /* const int for num rows    */
        static const int COLS = 25;    /* const int for num columns */
    
    protected:
    private:

    // API 
    public:
        Cell(int params[4]);
        ~Cell();
        bool addNeighbour(Cell &neighbour);
        Cell[] getNeighbours();
        int getDangerLevel();

    // Modules
    private:
        int m_x;                /* int for Cell x position */
        int m_y;                /* int for Cell y position */
        int m_w;                /* int for Cell width   */
        int m_h;                /* int for Cell height  */
        int m_proximity;        /* int for proximity    */
        Cell[8] m_neighbours;   /* Cell array for adjaent neighbours */
};

#endif /* Cell_hpp */