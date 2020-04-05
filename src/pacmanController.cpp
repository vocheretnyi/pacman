#include "pacmanController.h"

#include <climits>
#include <cassert>
#include <cmath>
#include <iostream>
#include <chrono>

#include "point.h"
#include "game_map.h"
#include "ghost.h"
#include "pacman.h"
#include "path_finder.h"

using namespace std;

constexpr size_t MAX_DEPTH = 6;

void rec(const Point& pacManPos, const deque<Ghost>& ghosts, const GameMap& gameMap, vector<vector<bool>>& cookies,
         double& bestScore, Point& bestPoint, double curScore, vector<Point>& curPath, int depth = 0) {
    if (curScore + MAX_DEPTH - depth <= bestScore) {
        return;
    }
    if (depth == MAX_DEPTH) {
        if (curScore > bestScore) {
            bestScore = curScore;
            bestPoint = curPath[0];
        }
        return;
    }

    auto neighbours = gameMap.getNeighbours(pacManPos);
    assert(!neighbours.empty());

    for (const Point& neighbour : neighbours) {
        if (curPath.size() > 1 && neighbours.size() > 1 && curPath[curPath.size() - 2] == neighbour &&
            (neighbour.x % 2 == 0 || neighbour.y % 2 == 0)) {
//            continue;
        }
        curPath.push_back(neighbour);
        bool wasCookie = cookies[neighbour.x][neighbour.y];
        cookies[neighbour.x][neighbour.y] = false;
        double nextScore = curScore;
        nextScore += wasCookie * pow(0.6, depth);
        nextScore -= gameMap.visited[neighbour.x][neighbour.y] / 50.0f;

        for (const Ghost& ghost : ghosts) {
            Point ghostPos = gameMap.convertToMapCoordinates(ghost.getPosition());
//            auto start = std::chrono::system_clock::now();
            int dist = PathFinder::a_star(neighbour, ghostPos,
                                          gameMap).size(); // TODO: pre-calc with floyd, should consider other ghost?
//            auto end = std::chrono::system_clock::now();
//            std::chrono::duration<double> elapsed_seconds = end-start;
//            std::cout << elapsed_seconds.count() << "\n";
            if (dist <= depth * 1.5) {
                if (dist <= 1) {
                    nextScore -= 1000.0f;
                } else {
                    nextScore -= 500.0f / dist;
                }
            }
        }

        rec(neighbour, ghosts, gameMap, cookies, bestScore, bestPoint, nextScore, curPath, depth + 1);
        cookies[neighbour.x][neighbour.y] = wasCookie;
        curPath.pop_back();
    }

}

namespace PacManController {

Point GetDecision(const PacMan& pacMan, const std::deque<Ghost>& ghosts, const GameMap& gameMap) {
    size_t width = gameMap.getWidth();
    size_t height = gameMap.getHeight();
    vector<vector<bool>> cookies(width, vector<bool>(height, false));
    for (const auto& cookie : gameMap.getCookies()) {
        Point p = gameMap.convertToMapCoordinates(cookie.getPosition());
        cookies[p.x][p.y] = true;
    }

    Point pacManPos = gameMap.convertToMapCoordinates(pacMan.getPosition());
    auto neighbours = gameMap.getNeighbours(pacManPos);
    assert(!neighbours.empty());

    double bestScore = -1e18;
    Point bestPoint = neighbours[0];

    vector<Point> path;

    rec(pacManPos, ghosts, gameMap, cookies, bestScore, bestPoint, 0, path, 0);
//    std::cout << bestScore << "\n";
    return bestPoint;
}

}
