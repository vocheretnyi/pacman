#include "ghost.h"

#include <SFML/Graphics.hpp>
#include <queue>

static const sf::IntRect FRAME_EYES_LEFT(0, 0, 32, 32);
static const sf::IntRect FRAME_EYES_CENTER(32, 0, 32, 32);
static const sf::IntRect FRAME_EYES_RIGHT(64, 0, 32, 32);

Ghost::Ghost(std::string ghostTexture, const sf::Vector2f& size, double positionX, double positionY)
        : sf::RectangleShape(size) {
    setPosition(positionX, positionY);
    texture.loadFromFile(ghostTexture);
    setTextureRect(FRAME_EYES_CENTER);
    setTexture(&texture);
    isWaiting_ = true;
    targetPoint = {-1, -1};
}

//void Ghost::setWay(const std::queue<sf::Vector2f>& way) {
//    this->way = way;
//    if (!this->way.empty()) {
//        targetPoint = this->way.front();
//        this->way.pop();
//    }
//}

void Ghost::update(float elapsedTime) {
    if (targetPoint == sf::Vector2f{-1, -1}) {
        return;
    }

    const float step = kSpeed * elapsedTime;

    float x = getPosition().x;
    float y = getPosition().y;
    float newX = x;
    float newY = y;

    if (x < targetPoint.x) {
        setTextureRect(FRAME_EYES_RIGHT);
        if (x + step > targetPoint.x) {
            newX = targetPoint.x;
        } else {
            newX = x + step;
        }
    } else if (newX > targetPoint.x) {
        setTextureRect(FRAME_EYES_LEFT);
        if (newX - step < targetPoint.x) {
            newX = targetPoint.x;
        } else {
            newX = x - step;
        }
    } else if (y < targetPoint.y) {
        setTextureRect(FRAME_EYES_CENTER);
        if (y + step > targetPoint.y) {
            newY = targetPoint.y;
        } else {
            newY = y + step;
        }
    } else if (y > targetPoint.y) {
        setTextureRect(FRAME_EYES_CENTER);
        if (y - step < targetPoint.y) {
            newY = targetPoint.y;
        } else {
            newY = y - step;
        }
    }

    if (newX == targetPoint.x && newY == targetPoint.y) {
        setTextureRect(FRAME_EYES_CENTER);
        isWaiting_ = true;
    }

    setPosition(newX, newY);
}

bool Ghost::isWaiting() const {
    return isWaiting_;
}

void Ghost::setTarget(sf::Vector2f target) {
    targetPoint = target;
    isWaiting_ = false;
}



