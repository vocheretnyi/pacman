#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "game_map.h"
#include "pacman.h"

class GameWindow : public sf::RenderWindow {
public:
    GameWindow(size_t width, size_t height, const char *title)
            : sf::RenderWindow(sf::VideoMode(width, height), title) {
        setFramerateLimit(MAX_FPS);
    }

    void handleEvents() {
        sf::Event event;
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                pacMan->setWay(gameMap->createWayTo(event.touch.x, event.touch.y, pacMan->getPosition()));
            }

        }
    }

    void render() {
        clear();
        drawMap();
        draw(*pacMan);
        display();
    }

    void drawMap() {
        for (int x = 0; x < gameMap->getWidth(); ++x) {
            for (int y = 0; y < gameMap->getHeight(); ++y) {
                draw(gameMap->getRectangles()[x][y]);
            }
        }
    }

    void setPacMan(PacMan *_pacMan) {
        pacMan = _pacMan;
    }

    void setGameMap(GameMap *_gameMap) {
        gameMap = _gameMap;
    }

private:
    const size_t MAX_FPS = 60;
    PacMan *pacMan;
    GameMap *gameMap;
};