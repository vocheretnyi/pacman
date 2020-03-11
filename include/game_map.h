#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

class Statistics;
class Point;

class GameMap {
public:
    GameMap(const std::string& mapFilePathName);

    size_t getWidth() const;

    size_t getHeight() const;

    float getBlockSize() const;

    const std::vector<std::vector<sf::RectangleShape>>& getRectangles() const;

    std::queue<sf::Vector2f> createWayTo(const sf::Vector2f& fn, const sf::Vector2f& st) const;

    Point convertToMapCoordinates(const sf::Vector2f& p) const;

    sf::Vector2f convertToWorldCoordinates(const Point& p) const;

    bool isWall(const Point& p) const;

    bool isFree(const Point& p) const;

    bool isCookie(const Point& p) const;

    bool isRoad(const Point& p) const;

    std::vector<Point> getNeighbours(const Point& p) const;

private:
    const float kBlockSize = 25.0;
    size_t width;
    size_t height;
    std::vector<std::vector<sf::RectangleShape>> rectangles;
    std::vector<std::string> fieldMaze;

    bool canGoTo(const Point& p) const;

    std::queue<sf::Vector2f> ConvertWayToWorldCoordinates(const std::vector<Point>& way) const;
};