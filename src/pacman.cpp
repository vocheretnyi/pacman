#include "pacman.h"

#include <SFML/Graphics.hpp>
#include <queue>

PacMan::PacMan(const std::string& pathToTexture, const sf::Vector2f& size, const sf::Vector2f& coord, float speed)
        : Monster(pathToTexture, size, coord, MonsterType::PACMAN, speed), cntCookies(0) {
}

void PacMan::setWay(const std::queue<sf::Vector2f>& way) {
    this->way = way;
    if (!this->way.empty()) {
        targetPoint = this->way.front();
        this->way.pop();
    }
}

void PacMan::update(float elapsedTime) {
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
        if (!way.empty()) {
            targetPoint = way.front();
            way.pop();
            isWaiting_ = false;
        } else {
            targetPoint = {-1, -1};
            isWaiting_ = true;
        }
    }

    setPosition(newX, newY);
}

void PacMan::eatCookie() {
    cntCookies++;
}

size_t PacMan::getCookieCount() const {
    return cntCookies;
}
