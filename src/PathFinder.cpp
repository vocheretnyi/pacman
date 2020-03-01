#include "PathFinder.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

#include "statistics.h"

using namespace std;

PathFinder::PathFinder() : width(0), height(0), gameMap({}) {}

PathFinder::PathFinder(int _width, int _height, const vector<string>& _gameMap)
        : width(_width), height(_height), gameMap(_gameMap) {}

bool PathFinder::canGoTo(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height && gameMap[y][x] == ' ';
}

vector<sf::Vector2i> PathFinder::dfs(int st_x, int st_y, int fn_x, int fn_y) const {
    vector<vector<bool>> used(width);
    vector<vector<sf::Vector2i>> parent(width);
    for (int i = 0; i < width; ++i) {
        used[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
            used[i][j] = false;
            parent[i][j] = {i, j};
        }
    }
    used[st_x][st_y] = true;
    parent[st_x][st_y] = {st_x, st_y};
    Statistics dfsStats("DFS");

    bool res = dfsHelper(st_x, st_y, fn_x, fn_y, 0, used, parent, dfsStats);

    vector<sf::Vector2i> way = getWayToTargetBaseOnParent(fn_x, fn_y, parent);

    dfsStats.setPathLength(way.size());
    cout << dfsStats << "\n";
    return way;
}

bool PathFinder::dfsHelper(int st_x, int st_y, int fn_x, int fn_y, int depth, vector<vector<bool>>& used,
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

vector<sf::Vector2i> PathFinder::bfs(int st_x, int st_y, int fn_x, int fn_y) const {
    queue<sf::Vector2i> q;
    q.push({st_x, st_y});
    vector<vector<int>> d(width);
    vector<vector<sf::Vector2i>> parent(width);
    for (int i = 0; i < width; ++i) {
        d[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
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

    vector<sf::Vector2i> way = getWayToTargetBaseOnParent(fn_x, fn_y, parent);

    bfsStats.setPathLength(way.size());
    cout << bfsStats << "\n";
    return way;
}

vector<sf::Vector2i>
PathFinder::getWayToTargetBaseOnParent(int fn_x, int fn_y, const vector<vector<sf::Vector2i>>& parent) const {
    vector<sf::Vector2i> reversedWay;

    sf::Vector2i pos{fn_x, fn_y};
    while (parent[fn_x][fn_y] != sf::Vector2i{fn_x, fn_y}) {
        reversedWay.emplace_back(fn_x, fn_y);
        int oldX = fn_x;
        int oldY = fn_y;
        fn_x = parent[oldX][oldY].x;
        fn_y = parent[oldX][oldY].y;
    }

    reverse(reversedWay.begin(), reversedWay.end());

    return reversedWay;
}