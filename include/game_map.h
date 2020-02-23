#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <algorithm>

static const char FIELD_MAZE[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

class GameMap {
public:
    GameMap(size_t width = 32, size_t height = 24) // TODO: change
    : _width(width)
    , _height(height) {
        _rectangles.resize(_width);
        for (int x = 0; x < _width; ++x) {
            _rectangles[x].resize(_height);
            for (int y = 0; y < _height; ++y) {
                _rectangles[x][y].setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                _rectangles[x][y].setSize(sf::Vector2f{BLOCK_SIZE, BLOCK_SIZE});
                _rectangles[x][y].setFillColor(
                        FIELD_MAZE[y * _width + x]
                        ? sf::Color(52, 93, 199)
                        : sf::Color(40, 40, 40)
                        ); // TODO: change
            }
        }
    }

    size_t getWidth() const {
        return _width;
    }

    size_t getHeight() const {
        return _height;
    }

    const std::vector<std::vector<sf::RectangleShape>>& getRectangles() const {
        return _rectangles;
    }

    std::queue<sf::Vector2i> createWayTo(float x, float y, const sf::Vector2f startPos) const {
        int fn_x = Round(x, BLOCK_SIZE);
        int fn_y = Round(y, BLOCK_SIZE);

        int st_x = Round(startPos.x, BLOCK_SIZE);
        int st_y = Round(startPos.y, BLOCK_SIZE);

        return bfs(st_x, st_y, fn_x, fn_y);
    }

private:
    const float BLOCK_SIZE = 25.0;
    size_t _width;
    size_t _height;
    std::vector<std::vector<sf::RectangleShape> >_rectangles;

    static int Round(float x, float BLOCK_SIZE) {
        return static_cast<int>(x / BLOCK_SIZE);
    }

    std::queue<sf::Vector2i> bfs(int st_x, int st_y, int fn_x, int fn_y) const {
        static const int INF = 1e9;
        std::queue<std::pair<int, int>> q;
        q.push({st_x, st_y});
        std::vector<std::vector<int>> d;
        std::vector<std::vector<std::pair<int, int>>> parent;
        d.resize(_width);
        parent.resize(_width);
        for (int i = 0; i < _width; ++i) {
            d[i].resize(_height);
            parent[i].resize(_height);
            for (int j = 0; j < _height; ++j) {
                d[i][j] = INF;
                parent[i][j] = {i, j};
            }
        }
        d[st_x][st_y] = 0;
        parent[st_x][st_y] = {st_x, st_y};
        while (!q.empty()) {
            int cur_x = q.front().first;
            int cur_y = q.front().second;
            q.pop();
            for (std::pair<int,int> delta : std::vector<std::pair<int,int>>{
                    {-1, 0},
                    {0, -1},
                    {1, 0},
                    {0, 1}
            }) {
                int to_x = cur_x + delta.first;
                int to_y = cur_y + delta.second;
                if (to_x >= 0 && to_y >= 0 && to_x < _width && to_y < _height) {
                    if (!FIELD_MAZE[to_x + to_y * _width]) {
                        if (d[cur_x][cur_y] + 1 < d[to_x][to_y]) {
                            d[to_x][to_y] = d[cur_x][cur_y] + 1;
                            parent[to_x][to_y] = {cur_x, cur_y};
                            q.push({to_x, to_y});
                        }
                    }
                }
            }
        }

        std::vector<sf::Vector2i> reversedWay;

        std::pair<int, int> pos{fn_x, fn_y};
        while (parent[fn_x][fn_y].first != fn_x || parent[fn_x][fn_y].second != fn_y) {
            reversedWay.push_back({fn_x, fn_y});
            int oldX = fn_x;
            int oldY = fn_y;
            fn_x = parent[oldX][oldY].first;
            fn_y = parent[oldX][oldY].second;
        }

        reverse(reversedWay.begin(), reversedWay.end());

        std::queue<sf::Vector2i> way;

        for (const auto& point : reversedWay) {
            way.push(sf::Vector2i{point.x * (int)BLOCK_SIZE, point.y * (int)BLOCK_SIZE});
        }

        return way;
    }
};