#pragma once

#include <deque>

class Ghost;

class GameMap;

class Point;

class PacMan;

namespace PacManController {

Point GetDecision(const PacMan& pacMan, const std::deque<Ghost>& ghosts, const GameMap& gameMap);

}
