#include "game_map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <cassert>

#include "path_finder.h"
#include "point.h"

using namespace std;

static const sf::Color WALL_COLOR = sf::Color(52, 93, 199);
static const sf::Color ROAD_COLOR = sf::Color(40, 40, 40);
static const sf::Color COOKIE_COLOR = sf::Color(255, 255, 255);

static const char WALL_MARKER = '#';
static const char UNREACHABLE_MARKER = '!';
static const char ROAD_MARKER = ' ';
static const char COOKIE_MARKER = '.';

const vector<Point> neighboursDeltas = {{-1, 0}, {0,  -1}, {1,  0}, {0,  1}};

static const sf::Color& getCorrectColor(char ch) {
    if (ch == WALL_MARKER) {
        return WALL_COLOR;
    } else if (ch == ROAD_MARKER || ch == UNREACHABLE_MARKER) {
        return ROAD_COLOR;
    } else if (ch == COOKIE_MARKER) {
        return COOKIE_COLOR;
    }
    assert(false);
    return sf::Color::Black;
}

GameMap::GameMap(const string& mapFilePathName) {
    ifstream in(mapFilePathName);
    in >> width >> height;
    in.ignore();
    fieldMaze.resize(height);
    for (string& line : fieldMaze) {
        getline(in, line);
    }

    rectangles.resize(width);
    for (int x = 0; x < width; ++x) {
        rectangles[x].resize(height);
        for (int y = 0; y < height; ++y) {
            rectangles[x][y].setPosition(x * kBlockSize, y * kBlockSize);
            rectangles[x][y].setSize(sf::Vector2f{kBlockSize, kBlockSize});
            rectangles[x][y].setFillColor(getCorrectColor(fieldMaze[y][x]));
        }
    }
}

size_t GameMap::getWidth() const {
    return width;
}

size_t GameMap::getHeight() const {
    return height;
}

float GameMap::getBlockSize() const {
    return kBlockSize;
}

const vector<vector<sf::RectangleShape>>& GameMap::getRectangles() const {
    return rectangles;
}

queue<sf::Vector2f> GameMap::createWayTo(const sf::Vector2f& to, const sf::Vector2f& from) const {
    Point fn = convertToMapCoordinates(to);
    Point st = convertToMapCoordinates(from);

    auto res1 = ConvertWayToWorldCoordinates(PathFinder::dfs(st, fn, *this));
    auto res2 = ConvertWayToWorldCoordinates(PathFinder::bfs(st, fn, *this));
    auto res3 = ConvertWayToWorldCoordinates(PathFinder::greedy(st, fn, *this));
    auto res4 = ConvertWayToWorldCoordinates(PathFinder::a_star(st, fn, *this));

    return res4;
}

std::vector<Point> GameMap::getNeighbours(const Point& cur) const {
    std::vector<Point> res;
    for (const Point& delta : neighboursDeltas) {
        Point to = cur + delta;
        if (canGoTo(to)) {
            res.push_back(to);
        }
    }
    return res;
}

queue<sf::Vector2f> GameMap::ConvertWayToWorldCoordinates(const vector<Point>& way) const {
    queue<sf::Vector2f> convertedWay;
    for (const auto& point : way) {
        convertedWay.push(convertToWorldCoordinates(point));
    }
    return convertedWay;
}

Point GameMap::convertToMapCoordinates(const sf::Vector2f& p) const {
    return {static_cast<int>(p.x / kBlockSize), static_cast<int>(p.y / kBlockSize)};
}

sf::Vector2f GameMap::convertToWorldCoordinates(const Point& p) const {
    return {p.x * kBlockSize, p.y * kBlockSize};
}

bool GameMap::isWall(const Point& p) const {
    return fieldMaze[p.y][p.x] == WALL_MARKER;
}

bool GameMap::isCookie(const Point& p) const {
    return fieldMaze[p.y][p.x] == COOKIE_MARKER;
}

bool GameMap::isRoad(const Point& p) const {
    return fieldMaze[p.y][p.x] == ROAD_MARKER;
}

bool GameMap::isFree(const Point& p) const {
    return fieldMaze[p.y][p.x] == ROAD_MARKER || fieldMaze[p.y][p.x] == COOKIE_MARKER;
}

bool GameMap::canGoTo(const Point& p) const {
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height && isFree(p);
}
