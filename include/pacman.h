#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "monster.h"

class PacMan : public Monster {
public:
    PacMan(const std::string& pathToTexture, const sf::Vector2f& size, const sf::Vector2f& coord, float speed);

    void setWay(const std::queue<sf::Vector2f>& way);

    void update(float elapsedTime) override;

    void eatCookie();

    size_t getCookieCount() const;

private:
    std::queue<sf::Vector2f> way;
    size_t cntCookies;
};
