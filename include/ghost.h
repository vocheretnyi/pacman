#pragma once

#include <SFML/Graphics.hpp>

#include "Monster.h"

class Ghost : public Monster {
public:
    Ghost(const std::string& ghostTexture, const sf::Vector2f& size, const sf::Vector2f& coord);

    void update(float elapsedTime) override;
};
