#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Statistics;

bool operator<(const sf::Vector2i& a, const sf::Vector2i& b);

class PathFinder {
public:

    PathFinder();

    PathFinder(int _width, int _height, const std::vector<std::string>& _gameMap);

    std::vector<sf::Vector2i> dfs(int st_x, int st_y, int fn_x, int fn_y) const;

    std::vector<sf::Vector2i> bfs(int st_x, int st_y, int fn_x, int fn_y) const;

    std::vector<sf::Vector2i> greedy(int st_x, int st_y, int fn_x, int fn_y) const;

    std::vector<sf::Vector2i> a_star(int st_x, int st_y, int fn_x, int fn_y) const;

private:
    static const int INF = 1e9;
    int width;
    int height;
    std::vector<std::string> gameMap;

    bool canGoTo(int x, int y) const;

    bool dfsHelper(int st_x, int st_y, int fn_x, int fn_y, int depth, std::vector<std::vector<bool>>& used,
                   std::vector<std::vector<sf::Vector2i>>& parent, Statistics& stats) const;

    std::vector<sf::Vector2i>
    getWayToTargetBaseOnParent(int fn_x, int fn_y, const std::vector<std::vector<sf::Vector2i>>& parent) const;

    int GetHeuristicValue(int st_x, int st_y, int fn_x, int fn_y) const;
};