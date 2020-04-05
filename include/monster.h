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

    Monster(const std::string& pathToTexture, const sf::Vector2f& size, const sf::Vector2f& coord,
            MonsterType _monsterType = MonsterType::MONSTER, float speed = 150.0f);

    void setTarget(sf::Vector2f target);

    virtual void update(float elapsedTime);

    bool isWaiting() const;

    void stopMoving();

    MonsterType getMonsterType() const;

protected:
    float kSpeed;
    sf::Vector2f targetPoint = {-1, -1};
    sf::Texture texture;
    bool isWaiting_;
    MonsterType monsterType;
};
