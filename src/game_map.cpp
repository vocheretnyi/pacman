#include "game_map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "statistics.h"
#include "PathFinder.h"

using namespace std;

GameMap::GameMap(size_t width, size_t height)
        : _width(width), _height(height) {
    pathFinder = PathFinder(_width, _height, FIELD_MAZE);
    _rectangles.resize(_width);
    for (int x = 0; x < _width; ++x) {
        _rectangles[x].resize(_height);
        for (int y = 0; y < _height; ++y) {
            _rectangles[x][y].setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
            _rectangles[x][y].setSize(sf::Vector2f{BLOCK_SIZE, BLOCK_SIZE});
            _rectangles[x][y].setFillColor(
                    FIELD_MAZE[y][x] == '#'
                    ? sf::Color(52, 93, 199)
                    : sf::Color(40, 40, 40)
            ); // TODO: change
        }
    }
}

size_t GameMap::getWidth() const {
    return _width;
}

size_t GameMap::getHeight() const {
    return _height;
}

const vector<vector<sf::RectangleShape>>& GameMap::getRectangles() const {
    return _rectangles;
}

queue<sf::Vector2f> GameMap::createWayTo(float x, float y, const sf::Vector2f& startPos) const {
    int fn_x = Round(x, BLOCK_SIZE);
    int fn_y = Round(y, BLOCK_SIZE);

    int st_x = Round(startPos.x, BLOCK_SIZE);
    int st_y = Round(startPos.y, BLOCK_SIZE);

    auto res1 = ConvertToMapCoordinates(pathFinder.dfs(st_x, st_y, fn_x, fn_y));
    auto res2 = ConvertToMapCoordinates(pathFinder.bfs(st_x, st_y, fn_x, fn_y));

    return res2;
}

queue<sf::Vector2f> GameMap::ConvertToMapCoordinates(const vector<sf::Vector2i>& way) const {
    queue<sf::Vector2f> convertedWay;
    for (const auto& point : way) {
        convertedWay.push({point.x * BLOCK_SIZE, point.y * BLOCK_SIZE});
    }
    return convertedWay;
}

int GameMap::Round(float x, float BLOCK_SIZE) {
    return static_cast<int>(x / BLOCK_SIZE);
}