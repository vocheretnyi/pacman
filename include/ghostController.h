#pragma once

#include <deque>

class Ghost;

class GameMap;

class Point;

class PacMan;

namespace GhostController {

Point GetDecision(const PacMan& pacMan, const Ghost& ghost, const GameMap& gameMap);

}
