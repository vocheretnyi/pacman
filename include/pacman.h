#pragma once

#include <SFML/Graphics.hpp>

class PacMan : public sf::CircleShape {
public:
    PacMan(double radius, double positionX = 0.0, double positionY = 0.0)
            : sf::CircleShape(radius) {
        setFillColor(sf::Color::Yellow);
        setPosition(positionX, positionY);
    }

    void handleMousePress(const int x, const int y) {
        targetPoint = {x, y};
    }

    void update(float elapsedTime) {
        if (targetPoint == sf::Vector2i{-1, -1}) {
            return;
        }
        const float step = SPEED * elapsedTime;
        const float delta = 1;

        float newX = getPosition().x;
        float newY = getPosition().y;

        if (newX + delta < targetPoint.x) {
            newX += step;
        } else if (newX - delta > targetPoint.x) {
            newX -= step;
        } else if (newY + delta < targetPoint.y) {
            newY += step;
        } else if (newY - delta > targetPoint.y) {
            newY -= step;
        }

        setPosition(newX, newY);
    }

private:
    const float SPEED = 100.0;
    sf::Vector2i targetPoint = {-1, -1};
};
