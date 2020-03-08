#include "game_map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "statistics.h"
#include "path_finder.h"

using namespace std;

GameMap::GameMap() {
    width = FIELD_MAZE[0].size();
    height = FIELD_MAZE.size();
    pathFinder = PathFinder(width, height, FIELD_MAZE);
    rectangles.resize(width);
    for (int x = 0; x < width; ++x) {
        rectangles[x].resize(height);
        for (int y = 0; y < height; ++y) {
            rectangles[x][y].setPosition(x * kBlockSize, y * kBlockSize);
            rectangles[x][y].setSize(sf::Vector2f{kBlockSize, kBlockSize});
            rectangles[x][y].setFillColor(
                    FIELD_MAZE[y][x] == '#'
                    ? sf::Color(52, 93, 199)
                    : sf::Color(40, 40, 40)
            ); // TODO: change
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
    Point fn = Round(to);
    Point st = Round(from);

    auto res1 = ConvertToMapCoordinates(pathFinder.dfs(st, fn));
    auto res2 = ConvertToMapCoordinates(pathFinder.bfs(st, fn));
    auto res3 = ConvertToMapCoordinates(pathFinder.greedy(st, fn));
    auto res4 = ConvertToMapCoordinates(pathFinder.a_star(st, fn));

    return res4;
}

void GameMap::Test() const {
    for (int st_x = 0; st_x < width; ++st_x) {
        for (int st_y = 0; st_y < height; ++st_y) {
            if (FIELD_MAZE[st_y][st_x] != '#')
                for (int fn_x = 0; fn_x < width; ++fn_x) {
                    for (int fn_y = 0; fn_y < height; ++fn_y) {
                        if (FIELD_MAZE[fn_y][fn_x] != '#')
                        {
                            auto res2 = ConvertToMapCoordinates(pathFinder.bfs({st_x, st_y}, {fn_x, fn_y}));
                            auto res4 = ConvertToMapCoordinates(pathFinder.a_star({st_x, st_y}, {fn_x, fn_y}));
                            assert(res2.size() == res4.size());
                        }
                    }
                }
        }
    }
}

queue<sf::Vector2f> GameMap::ConvertToMapCoordinates(const vector<Point>& way) const {
    queue<sf::Vector2f> convertedWay;
    for (const auto& point : way) {
        convertedWay.push({point.x * kBlockSize, point.y * kBlockSize});
    }
    return convertedWay;
}

Point GameMap::Round(const sf::Vector2f& p) const {
    return {static_cast<int>(p.x / kBlockSize), static_cast<int>(p.y / kBlockSize)};
}