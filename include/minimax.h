#pragma once

class PacMan;
class Ghost;
class GameMap;
class Point;

namespace MiniMax {

Point GetDecision(const Ghost& ghost, const PacMan& pacMan, const GameMap& gameMap);

}