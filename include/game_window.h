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
            }
        }
    }

    void render() {
        clear();
        drawMap();
        draw(*pacMan);
        drawGhosts();
        drawCookies();
        display();
    }

    void drawGhosts() {
        for (const Ghost& ghost : *ghosts_) {
            draw(ghost);
        }
    }

    void drawMap() {
        const auto& cells = gameMap->getCells();
        for (const auto& column : cells) {
            for (const auto& cell : column) {
                draw(cell.rectangle);
            }
        }
    }

    void drawCookies() {
        for (const auto& cookie : gameMap->getCookies()) {
            draw(cookie);
        }
    }

    void setPacMan(PacMan *_pacMan) {
        pacMan = _pacMan;
    }

    void setGameMap(const GameMap *_gameMap) {
        gameMap = _gameMap;
    }

    void setGhosts(const std::deque<Ghost> *ghosts) {
        ghosts_ = ghosts;
    }

private:
    const size_t kMaxFPS = 60;
    PacMan *pacMan;
    const GameMap *gameMap;
    const std::deque<Ghost> *ghosts_;
};