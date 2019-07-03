#include "Minesweeper.hpp"

int main(int argc, char const *argv[])
{
    Minesweeper ms = Minesweeper(NULL);
    ms.init(500, 500);
    ms.printBoard();
    return 0;
}