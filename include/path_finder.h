#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "point.h"

class Statistics;

class PathFinder {
public:

    PathFinder();

    PathFinder(int _width, int _height, const std::vector<std::string>& _gameMap);

    std::vector<Point> dfs(const Point& st, const Point& fn) const;

    std::vector<Point> bfs(const Point& st, const Point& fn) const;

    std::vector<Point> greedy(const Point& st, const Point& fn) const;

    std::vector<Point> a_star(const Point& st, const Point& fn) const;

private:
    static const int INF = 1e9;
    static const std::vector<Point> neighboursDeltas;
    int width;
    int height;
    std::vector<std::string> gameMap;

    bool canGoTo(const Point& p) const;

    bool dfsHelper(const Point& st, const Point& fn, std::vector<std::vector<bool>>& used,
                   std::vector<std::vector<Point>>& parent, Statistics& stats) const;

    std::vector<Point>
    getWayToTargetBaseOnParent(Point fn, const std::vector<std::vector<Point>>& parent) const;

    int GetHeuristicValue(const Point& st, const Point& fn) const;

    std::vector<Point> getNeighbours(const Point& p) const;
};