#include "Minesweeper.hpp"

int main(int argc, char const *argv[])
{
    Minesweeper ms = Minesweeper(NULL);
    ms.init(10, 10);
    ms.printBoard();
    return 0;
}