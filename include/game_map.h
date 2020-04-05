#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "point.h"
#include "cell.h"

class Statistics;

class Monster;

class Point;


class GameMap {
public:
    GameMap(const std::string& mapFilePathName);

    // Getters

    size_t getWidth() const;

    size_t getHeight() const;

    float getBlockSize() const;

    const std::vector<std::vector<Cell>>& getCells() const;

    const std::vector<sf::RectangleShape>& getCookies() const;

    const Point& getPacmanInitCoords() const;

    const std::vector<Point>& getGhostsInitCoords() const;

    // Other funcs

    std::queue<sf::Vector2f> createWayTo(const sf::Vector2f& fn, const sf::Vector2f& st) const;

    Point convertToMapCoordinates(const sf::Vector2f& p) const;

    sf::Vector2f convertToWorldCoordinates(const Point& p) const;

    std::vector<Point> getNeighbours(const Point& p, bool isForGhost = false) const;

//    bool checkPacmanAtCookie(const Monster *pacman);

    // assume that point p is a cookies cell
    void eatCookie(const Point& p);

    // Helpers

    bool isWall(const Point& p) const;

    bool isRoadOnly(const Point& p) const;

    bool isCookie(const Point& p) const;

    bool isRoad(const Point& p) const;

    std::vector<std::vector<double>> visited;

    void setGhostsPositions(std::vector<Point> ghostsPos, bool value = true);

private:
    const float kBlockSize = 25.0;
    size_t width;
    size_t height;
    std::vector<std::vector<Cell>> cells;
    sf::Texture cookieTexture;
    std::vector<sf::RectangleShape> cookies;
    std::vector<Point> ghostsInitCoords;
    Point pacmanInitCoords;

    bool canGoTo(const Point& p) const;

    std::queue<sf::Vector2f> ConvertWayToWorldCoordinates(const std::vector<Point>& way) const;
};