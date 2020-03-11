#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <functional>

class Ghost : public sf::RectangleShape {
public:
    Ghost(std::string ghostTexture, const sf::Vector2f& size, double positionX = 0.0, double positionY = 0.0);

    void setTarget(sf::Vector2f target);

    void update(float elapsedTime);

    bool isWaiting() const;

private:
    const float kSpeed = 150.0; // pixels per second
    sf::Vector2f targetPoint = {-1, -1};
    std::queue<sf::Vector2f> way;
    sf::Texture texture;
    bool isWaiting_;
};
