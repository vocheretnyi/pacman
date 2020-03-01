#include "pacman.h"

#include <SFML/Graphics.hpp>
#include <queue>

PacMan::PacMan(std::string pacmanTexture, double radius, double positionX, double positionY)
        : sf::CircleShape(radius) {
    setPosition(positionX, positionY);
    texture.loadFromFile(pacmanTexture);
    setTexture(&texture);
}

void PacMan::setWay(const std::queue<sf::Vector2f>& way) {
    this->way = way;
    if (!this->way.empty()) {
        targetPoint = this->way.front();
        this->way.pop();
    }
}

void PacMan::update(float elapsedTime) {
    if (targetPoint == sf::Vector2f{-1, -1}) {
        return;
    }

    const float step = SPEED * elapsedTime;

    float x = getPosition().x;
    float y = getPosition().y;
    float newX = x;
    float newY = y;

    if (x < targetPoint.x) {
        if (x + step > targetPoint.x) {
            newX = targetPoint.x;
        } else {
            newX = x + step;
        }
    } else if (newX > targetPoint.x) {
        if (newX - step < targetPoint.x) {
            newX = targetPoint.x;
        } else {
            newX = x - step;
        }
    } else if (y < targetPoint.y) {
        if (y + step > targetPoint.y) {
            newY = targetPoint.y;
        } else {
            newY = y + step;
        }
    } else if (y > targetPoint.y) {
        if (y - step < targetPoint.y) {
            newY = targetPoint.y;
        } else {
            newY = y - step;
        }
    }

    if (newX == targetPoint.x && newY == targetPoint.y) {
        if (!way.empty()) {
            targetPoint = way.front();
            way.pop();
        } else {
            targetPoint = {-1, -1};
        }
    }

    setPosition(newX, newY);
}


