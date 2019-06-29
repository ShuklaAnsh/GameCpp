#include "Minesweeper.hpp"
#include "Cell.hpp"

int main(int argc, char const *argv[])
{
    Cell cell = Cell([5, 5, 5, 5]);
    Minesweeper ms = Minesweeper(NULL);
    ms.init(500, 500);
    return 0;
}