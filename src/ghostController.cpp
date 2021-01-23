#include "ghostController.h"

#include <climits>
#include <cassert>
#include <cmath>
#include <iostream>
#include <chrono>
#include <random>

#include "point.h"
#include "game_map.h"
#include "ghost.h"
#include "pacman.h"
#include "path_finder.h"

using namespace std;

static std::mt19937 gen;


namespace GhostController {

Point GetDecision(const PacMan& pacMan, const Ghost& ghost, const GameMap& gameMap) {
    auto ghostPos = gameMap.convertToMapCoordinates(ghost.getPosition());
    auto pacmanPos = gameMap.convertToMapCoordinates(pacMan.getPosition());
    std::uniform_int_distribution<> uid(0, 50);
    if (uid(gen) < 47) {
        auto res = PathFinder::a_star(ghostPos, pacmanPos, gameMap, true);
        if (!res.empty()) {
            return res[0];
        }
    }
    // make random move
    auto neighbours = gameMap.getNeighbours(ghostPos);
    assert(!neighbours.empty());
    int rnd = rand() % (neighbours.size());
    return neighbours[rnd];
}

}