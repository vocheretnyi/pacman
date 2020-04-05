#include "monster.h"

#include <SFML/Graphics.hpp>
#include <cassert>

Monster::Monster(const std::string& pathToTexture, const sf::Vector2f& size, const sf::Vector2f& coord,
                 MonsterType _monsterType, float speed)
        : sf::RectangleShape(size), monsterType(_monsterType), kSpeed(speed) {
    setPosition(coord);
    texture.loadFromFile(pathToTexture);
    setTexture(&texture);
    isWaiting_ = true;
    targetPoint = {-1, -1};
}

void Monster::update(float elapsedTime) {
    if (targetPoint == sf::Vector2f{-1, -1}) {
        return;
    }

    const float step = kSpeed * elapsedTime;

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
        isWaiting_ = true;
    }

    setPosition(newX, newY);
}

bool Monster::isWaiting() const {
    return isWaiting_;
}

void Monster::setTarget(sf::Vector2f target) {
    targetPoint = target;
    isWaiting_ = false;
}

MonsterType Monster::getMonsterType() const {
    return monsterType;
}

void Monster::stopMoving() {
    isWaiting_ = true;
    targetPoint = {-1, -1};
}
