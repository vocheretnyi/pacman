#include "path_finder.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

#include "statistics.h"

using namespace std;

const vector<Point> PathFinder::neighboursDeltas = {{-1, 0},
                                                    {0,  -1},
                                                    {1,  0},
                                                    {0,  1}};

PathFinder::PathFinder() : width(0), height(0), gameMap({}) {}

PathFinder::PathFinder(int _width, int _height, const vector<string>& _gameMap)
        : width(_width), height(_height), gameMap(_gameMap) {}

bool PathFinder::canGoTo(const Point& p) const {
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height && gameMap[p.y][p.x] == ' ';
}

vector<Point> PathFinder::dfs(const Point& st, const Point& fn) const {
    vector<vector<bool>> used(width);
    vector<vector<Point>> parent(width);
    for (int i = 0; i < width; ++i) {
        used[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
            used[i][j] = false;
            parent[i][j] = {i, j};
        }
    }
    used[st.x][st.y] = true;
    parent[st.x][st.y] = st;
    Statistics dfsStats("DFS");

    bool res = dfsHelper(st, fn, used, parent, dfsStats);

    vector<Point> way = getWayToTargetBaseOnParent(fn, parent);

    dfsStats.setPathLength(way.size());
    cout << dfsStats << "\n";
    return way;
}

bool PathFinder::dfsHelper(const Point& st, const Point& fn, vector<vector<bool>>& used,
                           vector<vector<Point>>& parent, Statistics& stats) const {
    stats.increaseIterations();
    stats.addMemoryUsage(sizeof(int) * 5);
    if (st == fn) {
        stats.freeMemoryUsage(sizeof(int) * 5);
        return true;
    }
    for (const auto& to : getNeighbours(st)) {
        if (!used[to.x][to.y]) {
            used[to.x][to.y] = true;
            bool res = dfsHelper(to, fn, used, parent, stats);
            if (res) {
                parent[to.x][to.y] = st;
                stats.freeMemoryUsage(sizeof(int) * 5);
                return true;
            }
        }
    }
    stats.freeMemoryUsage(sizeof(int) * 5);
    return false;
}

vector<Point> PathFinder::bfs(const Point& st, const Point& fn) const {
    queue<Point> q;
    q.push(st);
    vector<vector<int>> d(width);
    vector<vector<Point>> parent(width);
    for (int i = 0; i < width; ++i) {
        d[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
            d[i][j] = INF;
            parent[i][j] = {i, j};
        }
    }
    d[st.x][st.y] = 0;
    parent[st.x][st.y] = st;
    Statistics bfsStats("BFS");
    bfsStats.addMemoryUsage(sizeof(q.front()));
    while (!q.empty()) {
        auto cur = q.front();
        bfsStats.increaseIterations();
        bfsStats.freeMemoryUsage(sizeof(q.front()));
        q.pop();
        if (cur == fn) {
            break;
        }
        for (const auto& to : getNeighbours(cur)) {
            if (d[cur.x][cur.y] + 1 < d[to.x][to.y]) {
                d[to.x][to.y] = d[cur.x][cur.y] + 1;
                parent[to.x][to.y] = cur;
                q.push(to);
                bfsStats.addMemoryUsage(sizeof(q.front()));
            }
        }
    }

    vector<Point> way = getWayToTargetBaseOnParent(fn, parent);

    bfsStats.setPathLength(way.size());
    cout << bfsStats << "\n";
    return way;
}

vector<Point> PathFinder::greedy(const Point& st, const Point& fn) const {
    set<pair<int, Point>> q;
    q.insert({GetHeuristicValue(st, fn), st});
    vector<vector<int>> d(width);
    vector<vector<Point>> parent(width);
    for (int i = 0; i < width; ++i) {
        d[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
            d[i][j] = 0;
            parent[i][j] = {i, j};
        }
    }
    d[st.x][st.y] = 1;
    parent[st.x][st.y] = st;
    Statistics greedyStats("GREEDY");
    greedyStats.addMemoryUsage(sizeof(*q.begin()));
    while (!q.empty()) {
        greedyStats.increaseIterations();
        auto cur = q.begin()->second;
        greedyStats.freeMemoryUsage(sizeof(*q.begin()));
        q.erase(q.begin());
        if (cur == fn) {
            break;
        }
        for (const auto& to : getNeighbours(cur)) {
            if (!d[to.x][to.y]) {
                int value = GetHeuristicValue(to, fn);
                d[to.x][to.y] = 1;
                parent[to.x][to.y] = cur;
                q.insert({value, to});
                greedyStats.addMemoryUsage(sizeof(*q.begin()));
            }
        }
    }

    vector<Point> way = getWayToTargetBaseOnParent(fn, parent);

    greedyStats.setPathLength(way.size());
    cout << greedyStats << "\n";
    return way;

}

vector<Point> PathFinder::a_star(const Point& st, const Point& fn) const {
    set<pair<int, Point>> q;
    q.insert({GetHeuristicValue(st, fn), st});
    vector<vector<int>> d(width);
    vector<vector<Point>> parent(width);
    for (int i = 0; i < width; ++i) {
        d[i].resize(height);
        parent[i].resize(height);
        for (int j = 0; j < height; ++j) {
            d[i][j] = INF;
            parent[i][j] = {i, j};
        }
    }
    d[st.x][st.y] = 0;
    parent[st.x][st.y] = st;
    Statistics aStarStats("A_STAR");
    aStarStats.addMemoryUsage(sizeof(*q.begin()));
    while (!q.empty()) {
        aStarStats.increaseIterations();
        Point cur = q.begin()->second;
        aStarStats.freeMemoryUsage(sizeof(*q.begin()));
        q.erase(q.begin());
        if (cur == fn) {
            break;
        }
        for (const auto& to : getNeighbours(cur)) {
            int newCost = d[cur.x][cur.y] + 1;
            if (newCost < d[to.x][to.y]) {
                d[to.x][to.y] = newCost;
                int value = GetHeuristicValue(to, fn);
                parent[to.x][to.y] = cur;
                q.insert({value + newCost, to});
                aStarStats.addMemoryUsage(sizeof(*q.begin()));
            }
        }
    }

    vector<Point> way = getWayToTargetBaseOnParent(fn, parent);

    aStarStats.setPathLength(way.size());
    cout << aStarStats << "\n";
    return way;
}

vector<Point>
PathFinder::getWayToTargetBaseOnParent(Point fn, const vector<vector<Point>>& parent) const {
    vector<Point> reversedWay;

    while (parent[fn.x][fn.y] != fn) {
        reversedWay.emplace_back(fn);
        fn = parent[fn.x][fn.y];
    }

    reverse(reversedWay.begin(), reversedWay.end());

    return reversedWay;
}

int PathFinder::GetHeuristicValue(const Point& st, const Point& fn) const {
    return abs(st.x - fn.x) + abs(st.y - fn.y);
}

std::vector<Point> PathFinder::getNeighbours(const Point& cur) const {
    std::vector<Point> res;
    for (const Point& delta : neighboursDeltas) {
        Point to = cur + delta;
        if (canGoTo(to)) {
            res.push_back(to);
        }
    }
    return res;
}

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}