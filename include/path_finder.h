#pragma once

#include <vector>

class Point;
class GameMap;

namespace PathFinder {

std::vector<Point> dfs(const Point& st, const Point& fn, const GameMap& gameMap);

std::vector<Point> bfs(const Point& st, const Point& fn, const GameMap& gameMap);

std::vector<Point> greedy(const Point& st, const Point& fn, const GameMap& gameMap);

std::vector<Point> a_star(const Point& st, const Point& fn, const GameMap& gameMap, bool isForGhost = false);

};
