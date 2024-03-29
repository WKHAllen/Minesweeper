#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "display.h"
#include <vector>

enum CellState {
    Space,
    Bomb,
    MarkedSpace,
    MarkedBomb,
    Revealed,
    Explosion
};

class Minesweeper {
    private:
        int w;
        int h;
        int bombs;
        bool playing;
        int marking[2];
        std::vector< std::vector<CellState> > board;
        std::vector< std::vector<int> > neighbors;
        Display screen;
        sf::Color borderColor;
        sf::Color unknownColor;
        sf::Color markedColor;
        sf::Color revealedColor;
        sf::Color bombColor;
        int bombNeighbors(int x, int y);
        void revealAll();
        void revealNeighbor(int x, int y);
        void removeZeros(int x, int y);
        void check(int x, int y);
        void mark(int x, int y);

    public:
        Minesweeper(int width, int height, int difficulty);
        void display();
        void run();
};

#endif // MINESWEEPER_H
