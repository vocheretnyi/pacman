#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "game_map.h"

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
                createWayTo()
                std::queue<sf::Vector2i> way;
                way.push({event.touch.x, event.touch.y});
                way.push({100, 100});
                way.push({625, 325});
                pacMan.setWay(way);
            }

        }
    }

    void render(const sf::Shape& shape, const GameMap& gameMap) {
        clear();
        drawMap(gameMap);
        draw(shape);
        display();
    }

    void drawMap(const GameMap& gameMap) {
        for (int x = 0; x < gameMap.getWidth(); ++x) {
            for (int y = 0; y < gameMap.getHeight(); ++y) {
                draw(gameMap.getRectangles()[x][y]);
            }
        }
    }

private:
    const size_t MAX_FPS = 60;
};