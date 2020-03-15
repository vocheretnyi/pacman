#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "Monster.h"

class PacMan : public Monster {
public:
    PacMan(const std::string& pacmanTexture, const sf::Vector2f& size, const sf::Vector2f& coord);

    void setWay(const std::queue<sf::Vector2f>& way);

    void update(float elapsedTime) override;

    void eatCookie();

private:
    std::queue<sf::Vector2f> way;
    size_t cntCookies;
};
