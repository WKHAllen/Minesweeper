#include "minesweeper.h"
#include <string>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int width = 0;
    int height = 0;
    int difficulty = -1;
    for (int i = 1; i < argc; i++) {
        if (((std::string)argv[i] == "-w" || (std::string)argv[i] == "--width") && i + 1 < argc) {
            width = atoi(argv[++i]);
        }
        else if (((std::string)argv[i] == "-h" || (std::string)argv[i] == "--height") && i + 1 < argc) {
            height = atoi(argv[++i]);
        }
        else if (((std::string)argv[i] == "-d" || (std::string)argv[i] == "--difficulty") && i + 1 < argc) {
            difficulty = atoi(argv[++i]);
        }
    }
    Minesweeper game(width, height, difficulty);
    game.run();
    return 0;
}
