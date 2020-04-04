#pragma once

class Monster;
class GameMap;
class Point;

namespace MiniMax {

Point GetDecision(const Monster* player1, const Monster* player2, const GameMap& gameMap);

}