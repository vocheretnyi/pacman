#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <algorithm>

#include "statistics.h"

using namespace std;

const vector<string> FIELD_MAZE = {
        {"!#######################!"},
        {"!#          #          #!"},
        {"!# ## ##### # ##### ## #!"},
        {"!#                     #!"},
        {"!# ## # ######### # ## #!"},
        {"!#    #     #     #    #!"},
        {"!#### ##### # ##### ####!"},
        {"!!!!# #           # #!!!!"},
        {"##### # # ##### # # #####"},
        {"#       # #   # #       #"},
        {"##### # # ##### # # #####"},
        {"!!!!# #           # #!!!!"},
        {"!#### # ######### # ####!"},
        {"!#          #          #!"},
        {"!# ## ##### # ##### ## #!"},
        {"!#  #               #  #!"},
        {"!## # # ######### # #  #!"},
        {"!#    #     #     #    #!"},
        {"!# ####### ### ####### #!"},
        {"!# #     #     #     # #!"},
        {"!# # ### ## # ## ### # #!"},
        {"!# # #      #      # # #!"},
        {"!# # # #### # #### # # #!"},
        {"!#          #          #!"},
        {"!#######################!"},
};

class GameMap {
public:
    GameMap(size_t width = 25, size_t height = 25) // TODO: change
            : _width(width), _height(height) {
        srand(time(NULL));
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

    size_t getWidth() const {
        return _width;
    }

    size_t getHeight() const {
        return _height;
    }

    const vector<vector<sf::RectangleShape>>& getRectangles() const {
        return _rectangles;
    }

    queue<sf::Vector2i> createWayTo(float x, float y, const sf::Vector2f startPos) const {
        int fn_x = Round(x, BLOCK_SIZE);
        int fn_y = Round(y, BLOCK_SIZE);

        int st_x = Round(startPos.x, BLOCK_SIZE);
        int st_y = Round(startPos.y, BLOCK_SIZE);

//        auto res1 = dfs(st_x, st_y, fn_x, fn_y);
        auto res2 = bfs(st_x, st_y, fn_x, fn_y);

        return res2;
    }

private:
    const float BLOCK_SIZE = 25.0;
    size_t _width;
    size_t _height;
    vector<vector<sf::RectangleShape> > _rectangles;

    static const int INF = 1e9;

    static int Round(float x, float BLOCK_SIZE) {
        return static_cast<int>(x / BLOCK_SIZE);
    }

    bool canGoTo(int x, int y) const {
        return x >= 0 && y >= 0 && x < _width && y < _height && FIELD_MAZE[y][x] == ' ';
    }

    queue<sf::Vector2i> dfs(int st_x, int st_y, int fn_x, int fn_y) const {
        vector<vector<bool>> used(_width);
        vector<vector<sf::Vector2i>> parent(_width);
        for (int i = 0; i < _width; ++i) {
            used[i].resize(_height);
            parent[i].resize(_height);
            for (int j = 0; j < _height; ++j) {
                used[i][j] = false;
                parent[i][j] = {i, j};
            }
        }
        used[st_x][st_y] = true;
        parent[st_x][st_y] = {st_x, st_y};
        Statistics dfsStats("DFS");

        bool res = dfsHelper(st_x, st_y, fn_x, fn_y, 0, used, parent, dfsStats);

        queue<sf::Vector2i> way = getWayToTargetBaseOnParent(fn_x, fn_y, parent);

        dfsStats.setPathLength(way.size());
        cout << dfsStats << "\n";
        return way;
    }

    bool dfsHelper(int st_x, int st_y, int fn_x, int fn_y, int depth, vector<vector<bool>>& used,
             vector<vector<sf::Vector2i>>& parent, Statistics& stats) const {
        stats.increaseIterations();
        stats.addMemoryUsage(sizeof(int) * 5);
        if (depth > 200) {
            used[st_x][st_y] = false;
            parent[st_x][st_y] = {st_x, st_y};
            return false;
        }
//        if (used[st_x][st_y]) {
//            return false;
//        }
        if (fn_x == st_x && fn_y == st_y) {
            return true;
        }
        for (sf::Vector2i delta : vector<sf::Vector2i>{
                {-1, 0},
                {0,  -1},
                {1,  0},
                {0,  1}
        }) {
            stats.addMemoryUsage(sizeof(delta));
            int to_x = st_x + delta.x;
            int to_y = st_y + delta.y;
            stats.addMemoryUsage(sizeof(int) * 2);
            if (canGoTo(to_x, to_y) && !used[to_x][to_y]) {
                used[to_x][to_y] = true;
                parent[to_x][to_y] = {st_x, st_y};
                bool res = dfsHelper(to_x, to_y, fn_x, fn_y, depth + 1, used, parent, stats);
//                    used[to_x][to_y] = false;
//                    parent[to_x][to_y] = {to_x, to_y};
                if (res) {
                    return true;
                }
            }
        }
        return false;
    }

    queue<sf::Vector2i> bfs(int st_x, int st_y, int fn_x, int fn_y) const {
        queue<sf::Vector2i> q;
        q.push({st_x, st_y});
        vector<vector<int>> d(_width);
        vector<vector<sf::Vector2i>> parent(_width);
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
        Statistics bfsStats("BFS");
        while (!q.empty()) {
            int cur_x = q.front().x;
            int cur_y = q.front().y;
            bfsStats.increaseIterations();
            q.pop();
            bfsStats.addMemoryUsage(sizeof(int) * 2);
            if (d[fn_x][fn_y] < d[cur_x][cur_y]) {
                continue;
            }
            for (const sf::Vector2i delta : vector<sf::Vector2i>{
                    {-1, 0},
                    {0,  -1},
                    {1,  0},
                    {0,  1}
            }) {
                bfsStats.addMemoryUsage(sizeof(delta));
                int to_x = cur_x + delta.x;
                int to_y = cur_y + delta.y;
                bfsStats.addMemoryUsage(sizeof(int) * 2);
                bfsStats.increaseIterations();
                if (canGoTo(to_x, to_y)) {
                    if (d[cur_x][cur_y] + 1 < d[to_x][to_y]) {
                        d[to_x][to_y] = d[cur_x][cur_y] + 1;
                        parent[to_x][to_y] = {cur_x, cur_y};
                        q.push({to_x, to_y});
                        bfsStats.addMemoryUsage(sizeof(q.front()));
                    }
                }
            }
        }

        queue<sf::Vector2i> way = getWayToTargetBaseOnParent(fn_x, fn_y, parent);

        bfsStats.setPathLength(way.size());
        cout << bfsStats << "\n";
        return way;
    }

    queue<sf::Vector2i> getWayToTargetBaseOnParent(int fn_x, int fn_y, const vector<vector<sf::Vector2i>>& parent) const {
        vector<sf::Vector2i> reversedWay;

        sf::Vector2i pos{fn_x, fn_y};
        while (parent[fn_x][fn_y] != sf::Vector2i {fn_x, fn_y}) {
            reversedWay.emplace_back(fn_x, fn_y);
            int oldX = fn_x;
            int oldY = fn_y;
            fn_x = parent[oldX][oldY].x;
            fn_y = parent[oldX][oldY].y;
        }

        reverse(reversedWay.begin(), reversedWay.end());

        queue<sf::Vector2i> way;

        for (const auto& point : reversedWay) {
            way.push(sf::Vector2i{point.x * (int) BLOCK_SIZE, point.y * (int) BLOCK_SIZE});
        }
        return way;
    }
    
};