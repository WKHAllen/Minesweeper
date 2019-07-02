#include "minesweeper.h"
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

Minesweeper::Minesweeper(int width, int height, int difficulty) {
    if (width == 0) {
        width = 40;
    }
    if (height == 0) {
        height = 30;
    }
    if (difficulty < 0 || difficulty > 100) {
        difficulty = 25;
    }
    w = width;
    h = height;
    bombs = width * height * difficulty / 100;
    playing = true;
    board.resize(w, std::vector<CellState>(h));
    neighbors.resize(w, std::vector<int>(h));
    srand(time(NULL));
    int bombsPlaced = 0;
    int x, y;
    while (bombsPlaced < bombs) {
        do {
            x = rand() % w;
            y = rand() % h;
        } while (board[x][y] == Bomb);
        board[x][y] = Bomb;
        bombsPlaced++;
    }
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            neighbors[i][j] = bombNeighbors(i, j);
        }
    }
    borderColor = sf::Color(64, 64, 64);
    unknownColor = sf::Color(192, 192, 192);
    markedColor = sf::Color(0, 192, 0);
    revealedColor = sf::Color(64, 64, 255);
    bombColor = sf::Color(255, 64, 64);
}

void Minesweeper::display() {
    screen.fill(borderColor);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (board[i][j] == Space || board[i][j] == Bomb) {
                screen.draw(i, j, unknownColor);
            }
            else if (board[i][j] == MarkedSpace || board[i][j] == MarkedBomb) {
                screen.draw(i, j, markedColor);
            }
            else if (board[i][j] == Revealed) {
                screen.draw(i, j, revealedColor);
                if (neighbors[i][j] > 0) {
                    screen.showNearby(i, j, neighbors[i][j]);
                }
            }
            else if (board[i][j] == Explosion) {
                screen.draw(i, j, bombColor);
            }
        }
    }
    screen.update();
}

int Minesweeper::bombNeighbors(int x, int y) {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i != x || j != y) {
                if (i >= 0 && i < w && j >= 0 && j < h && board[i][j] == Bomb) {
                    neighbors++;
                }
            }
        }
    }
    return neighbors;
}

void Minesweeper::revealAll() {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (board[i][j] == Bomb || board[i][j] == MarkedBomb) {
                board[i][j] = Explosion;
            }
            else if (board[i][j] == Space || board[i][j] == MarkedSpace) {
                board[i][j] = Revealed;
            }
        }
    }
}

void Minesweeper::revealNeighbor(int x, int y) {
    if (x >= 0 && x < w && y >= 0 && y < h && neighbors[x][y] != 0 && board[x][y] == Space) {
        board[x][y] = Revealed;
    }
}

void Minesweeper::removeZeros(int x, int y) {
    if (x >= 0 && x < w && y >= 0 && y < h && neighbors[x][y] == 0 && board[x][y] == Space) {
        board[x][y] = Revealed;
        removeZeros(x - 1, y);
        removeZeros(x, y - 1);
        removeZeros(x + 1, y);
        removeZeros(x, y + 1);
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                revealNeighbor(i, j);
            }
        }
    }
}

void Minesweeper::check(int x, int y) {
    if (board[x][y] == Bomb || board[x][y] == MarkedBomb) {
        board[x][y] = Explosion;
        revealAll();
        //playing = false;
    }
    else if (board[x][y] == Space) {
        removeZeros(x, y);
        board[x][y] = Revealed;
    }
}

void Minesweeper::mark(int x, int y) {
    if (board[x][y] == Space) {
        board[x][y] = MarkedSpace;
    }
    else if (board[x][y] == Bomb) {
        board[x][y] = MarkedBomb;
    }
    else if (board[x][y] == MarkedSpace) {
        board[x][y] = Space;
    }
    else if (board[x][y] == MarkedBomb) {
        board[x][y] = Bomb;
    }
    screen.draw(x, y, markedColor);
}

void Minesweeper::run() {
    // display instructions
    // add menu screen?
    screen.create(w, h, "Minesweeper");
    screen.fill(borderColor);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            screen.draw(i, j, unknownColor);
        }
    }
    sf::Vector2i pos;
    while (screen.isOpen() && playing) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            pos = sf::Mouse::getPosition(screen.window);
            check(pos.x / screen.cellSize, pos.y / screen.cellSize);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            pos = sf::Mouse::getPosition(screen.window);
            mark(pos.x / screen.cellSize, pos.y / screen.cellSize);
        }
        display();
    }
    if (!playing) {
        // display "you won" or "you lost"
        // close the screen after some user input
    }
}
