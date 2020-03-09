#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "game_map.h"
#include "pacman.h"
#include "ghost.h"

class GameWindow : public sf::RenderWindow {
public:
    GameWindow(size_t width, size_t height, const char *title)
            : sf::RenderWindow(sf::VideoMode(width, height), title) {
        setFramerateLimit(kMaxFPS);
    }

    void handleEvents() {
        sf::Event event;
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2f to(event.touch.x, event.touch.y);
                pacMan->setWay(gameMap->createWayTo(to, pacMan->getPosition()));
//                ghost->setWay(gameMap->createWayTo(to, ghost->getPosition()));
            }

        }
    }

    void render() {
        clear();
        drawMap();
        draw(*pacMan);
        draw(*ghost);
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

    void setGhost(Ghost *_ghost) {
        ghost = _ghost;
    }

private:
    const size_t kMaxFPS = 60;
    PacMan *pacMan;
    GameMap *gameMap;
    Ghost *ghost;
};