#include "path_finder.h"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

#include "game_map.h"
#include "statistics.h"
#include "point.h"

using namespace std;

static const int INF = 1e9;

int GetHeuristicValue(const Point& st, const Point& fn);

vector<Point> getWayToTargetBaseOnParent(Point fn, const vector<vector<Point>>& parent);

bool dfsHelper(const Point& st, const Point& fn, vector<vector<bool>>& used,
               vector<vector<Point>>& parent, Statistics& stats, const GameMap& gameMap);


namespace PathFinder {

vector<Point> dfs(const Point& st, const Point& fn, const GameMap& gameMap) {
    if (gameMap.isWall(fn)) {
        return {};
    }
    size_t width = gameMap.getWidth();
    size_t height = gameMap.getHeight();
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

    bool res = dfsHelper(st, fn, used, parent, dfsStats, gameMap);

    vector<Point> way = getWayToTargetBaseOnParent(fn, parent);

    dfsStats.setPathLength(way.size());
    cout << dfsStats << "\n";
    return way;
}

vector<Point> bfs(const Point& st, const Point& fn, const GameMap& gameMap) {
    if (gameMap.isWall(fn)) {
        return {};
    }
    size_t width = gameMap.getWidth();
    size_t height = gameMap.getHeight();
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
        for (const auto& to : gameMap.getNeighbours(cur)) {
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

vector<Point> greedy(const Point& st, const Point& fn, const GameMap& gameMap) {
    if (gameMap.isWall(fn)) {
        return {};
    }
    size_t width = gameMap.getWidth();
    size_t height = gameMap.getHeight();
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
        for (const auto& to : gameMap.getNeighbours(cur)) {
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

vector<Point> a_star(const Point& st, const Point& fn, const GameMap& gameMap, bool isForGhost) {
    if (gameMap.isWall(fn)) {
        return {};
    }
    size_t width = gameMap.getWidth();
    size_t height = gameMap.getHeight();
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
        for (const auto& to : gameMap.getNeighbours(cur, isForGhost)) {
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
//    cout << aStarStats << "\n";
    return way;
}

} // ns PathFinder

int GetHeuristicValue(const Point& st, const Point& fn) {
    return abs(st.x - fn.x) + abs(st.y - fn.y);
}

bool dfsHelper(const Point& st, const Point& fn, vector<vector<bool>>& used,
               vector<vector<Point>>& parent, Statistics& stats, const GameMap& gameMap) {
    stats.increaseIterations();
    stats.addMemoryUsage(sizeof(int) * 5);
    if (st == fn) {
        stats.freeMemoryUsage(sizeof(int) * 5);
        return true;
    }
    for (const auto& to : gameMap.getNeighbours(st)) {
        if (!used[to.x][to.y]) {
            used[to.x][to.y] = true;
            bool res = dfsHelper(to, fn, used, parent, stats, gameMap);
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

vector<Point> getWayToTargetBaseOnParent(Point fn, const vector<vector<Point>>& parent) {
    vector<Point> reversedWay;

    while (parent[fn.x][fn.y] != fn) {
        reversedWay.emplace_back(fn);
        fn = parent[fn.x][fn.y];
    }

    reverse(reversedWay.begin(), reversedWay.end());

    return reversedWay;
}