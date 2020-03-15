#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

enum class MonsterType {
    PACMAN,
    GHOST,
    MONSTER
};

class Monster : public sf::RectangleShape {
public:
    Monster(const std::string& _texture, const sf::Vector2f& size, const sf::Vector2f& coord, MonsterType _monsterType = MonsterType::MONSTER);

    void setTarget(sf::Vector2f target);

    virtual void update(float elapsedTime);

    bool isWaiting() const;

    MonsterType getMonsterType() const;

protected:
    const float kSpeed = 150.0; // pixels per second
    sf::Vector2f targetPoint = {-1, -1};
    sf::Texture texture;
    bool isWaiting_;
    MonsterType monsterType;
};
