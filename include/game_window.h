#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class GameWindow : public sf::RenderWindow {
public:
    GameWindow(size_t width, size_t height, const char* title)
            : sf::RenderWindow(sf::VideoMode(width, height), title) {
        setFramerateLimit(MAX_FPS);
    }

    void handleEvents(PacMan& pacMan) {
        sf::Event event;
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                pacMan.handleMousePress(event.touch.x, event.touch.y);
            }

        }
    }

    void render(const sf::Shape& shape) {
        clear();
        draw(shape);
        display();
    }

private:
    const size_t MAX_FPS = 60;
};