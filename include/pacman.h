#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

class PacMan : public sf::CircleShape {
public:
    PacMan(std::string pacmanTexture, double radius, double positionX = 0.0, double positionY = 0.0);

    void setWay(const std::queue<sf::Vector2f>& way);

    void update(float elapsedTime);

private:
    const float kSpeed = 150.0; // pixels per second
    sf::Vector2f targetPoint = {-1, -1};
    std::queue<sf::Vector2f> way;
    sf::Texture texture;
};
