#pragma once

#include <SFML/Graphics.hpp>

#include "monster.h"

class Ghost : public Monster {
public:

    Ghost(const std::string& pathToTexture, const sf::Vector2f& size, const sf::Vector2f& coord, float speed);

    Ghost(const Ghost& other) = delete;

    Ghost& operator=(const Ghost& other) = delete;

    void update(float elapsedTime) override;
};
