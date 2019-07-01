#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>

class Display {
    private:
        int w;
        int h;
        sf::Font font;

    public:
        int cellSize;
        sf::RenderWindow window;
        void create(int width, int height, std::string title);
        void fill(sf::Color color);
        void draw(int x, int y, sf::Color color);
        void showNearby(int x, int y, int nearby);
        void update();
        bool isOpen();
};

#endif // DISPLAY_H
