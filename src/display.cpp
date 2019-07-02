#include "display.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

void Display::create(int width, int height, std::string title) {
    w = width;
    h = height;
    cellSize = 20;
    window.create(sf::VideoMode(w * cellSize, h * cellSize), title);
    window.setVerticalSyncEnabled(true);
    font.loadFromFile("assets/fonts/Inconsolata-Bold.ttf");
}

void Display::fill(sf::Color color) {
    window.clear(color);
}

void Display::draw(int x, int y, sf::Color color) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
    cell.setFillColor(color);
    cell.setPosition(sf::Vector2f(cellSize * x + 1, cellSize * y + 1));
    window.draw(cell);
}

void Display::showNearby(int x, int y, int nearby) {
    std::ostringstream ss;
    ss << nearby;
    sf::Text text;
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(cellSize - 2);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x * cellSize + cellSize / 2.0f, y * cellSize + cellSize / 2.0f);
    window.draw(text);
}

void Display::update() {
    window.display();
}

bool Display::isOpen() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    return window.isOpen();
}
