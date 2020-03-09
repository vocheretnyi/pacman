#include "minimax.h"

#include <cassert>

#include "point.h"
#include "game_map.h"
#include "ghost.h"
#include "pacman.h"

using namespace std;

Point MiniMax::GetDecision(const Ghost& ghost, const PacMan& pacMan, const GameMap& gameMap) {
    auto ghostCoord = gameMap.convertToMapCoordinates(ghost.getPosition());
    auto pacmanCoord = gameMap.convertToMapCoordinates(pacMan.getPosition());
    auto neighbours = gameMap.getPathFinder().getNeighbours(ghostCoord);
    assert(!neighbours.empty());
    int rnd = rand() % (neighbours.size());
    return neighbours[rnd];
}
