#include "minimax.h"

#include <cassert>
#include <iostream>
//#include <algorithm>

#include "point.h"
#include "game_map.h"
#include "ghost.h"
#include "pacman.h"
#include "path_finder.h"

using namespace std;

const int MINIMAX_DEPTH = 4;
const int BIG_VALUE = 1e9;

pair<int, Point> NegaMax(Monster player1, Monster player2, GameMap gameMap, int depth, int coef, int cookies, int alpha, int beta) { // TODO: add reference or pointer
    if (player1.getGlobalBounds().intersects(player2.getGlobalBounds())) { // ghost kills pacman
        return {BIG_VALUE * -coef, {}};
    }
    Monster pacMan = player1.getMonsterType() == MonsterType::PACMAN ? player1 : player2;

    if (gameMap.isCookie(gameMap.convertToMapCoordinates(player1.getPosition()))) { // pacman or player1?
        gameMap.eatCookie(gameMap.convertToMapCoordinates(player1.getPosition()));
        ++cookies;
        if (gameMap.getCookies().size() == 0) {
            return {BIG_VALUE * -coef, {}};
        }
        // TODO: will check for all eaten cookies
//        if (pacMan.getCookieCount() == gameMap.getCookiesCount()) {
    }
    auto player1Coord = gameMap.convertToMapCoordinates(player1.getPosition());
    auto player2Coord = gameMap.convertToMapCoordinates(player2.getPosition());
    if (depth == 0) {
        if (player1.getMonsterType() == MonsterType::PACMAN) {
            int sum = 0;
            const auto& cookiesArray = gameMap.getCookies();
            Point pacmanCoord = gameMap.convertToMapCoordinates(pacMan.getPosition());
            size_t mn = BIG_VALUE;
            for (const auto& z : cookiesArray) {
                mn = min(mn, PathFinder::a_star(gameMap.convertToMapCoordinates(z.getPosition()), pacmanCoord,
                                                gameMap).size());
//            sum += sz;
            }
            int val = cookies * 100;
            val += (100 - mn) * 2;
            int ww = PathFinder::a_star(player1Coord, player2Coord, gameMap).size();
//            if (ww < 10) {
//                return {BIG_VALUE * coef, {}};
//            }
            int tt = (ww) * 100;
            return {(val + tt) * -coef, {}};
        } else {
            int w = PathFinder::a_star(player1Coord, player2Coord, gameMap).size();
            return {(100 - w) * 2 * -coef, {}};
        }
    }
    int maxScore = numeric_limits<int>::min();
    Point bestMove;


    auto neighbours = gameMap.getNeighbours(player1Coord);
    for (const Point& point : neighbours) {

        // make move for first player to point
        player1.setPosition(gameMap.convertToWorldCoordinates(point));

        int score = -NegaMax(player2, player1, gameMap, depth - 1, -coef, cookies, alpha, beta).first;
        if (score > maxScore) {
            maxScore = score;
            bestMove = point;
        }
//        if (player1.getMonsterType() == MonsterType::PACMAN) {
//            alpha = max(alpha, score);
//        } else {
//            beta = min(beta, score);
//        }
//        if (beta < alpha) {
//            break;
//        }
    }
    return {maxScore, move(bestMove)};
}

Point MiniMax::GetDecision(const Monster* player1, const Monster* player2, const GameMap& gameMap) {
    if (rand() % 20 > 1 || player1->getMonsterType() == MonsterType::PACMAN) { // calc minmax
        return NegaMax(*player1, *player2, gameMap, MINIMAX_DEPTH, -1, 0, -BIG_VALUE, BIG_VALUE).second; // TODO: coef?
    } else { // make random move
        auto player1Coord = gameMap.convertToMapCoordinates(player1->getPosition());
        auto neighbours = gameMap.getNeighbours(player1Coord);

        assert(!neighbours.empty());
        int rnd = rand() % (neighbours.size());
        return neighbours[rnd];
    }
}
