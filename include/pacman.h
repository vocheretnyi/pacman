#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

const char PACMAN_TEXTURE[] = "/home/vocheretnyi/CLionProjects/pac-man/pacman.png";

class PacMan : public sf::CircleShape {
public:
    PacMan(double radius, double positionX = 0.0, double positionY = 0.0)
            : sf::CircleShape(radius) {
        setPosition(positionX, positionY);
        texture.loadFromFile(PACMAN_TEXTURE);
        setTexture(&texture);
    }

    void setWay(const std::queue<sf::Vector2i>& way) {
        this->way = way;
        if (!this->way.empty()) {
            targetPoint = this->way.front();
            this->way.pop();
        }
    }

    void update(float elapsedTime) {
        if (targetPoint == sf::Vector2i{-1, -1}) {
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

private:
    const float SPEED = 150.0; // pixels per second
    sf::Vector2i targetPoint = {-1, -1};
    std::queue<sf::Vector2i> way;
    sf::Texture texture;
};
