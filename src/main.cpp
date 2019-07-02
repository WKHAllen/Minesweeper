#include "minesweeper.h"
#include <iostream>

int main()
{
    Minesweeper game(0, 0, 10);
    game.run();
    std::cout << "Game over";
    return 0;
}
