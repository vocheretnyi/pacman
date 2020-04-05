#pragma once

#include <SFML/Graphics.hpp>

#include "point.h"

enum class CellType {
    COOKIE,
    ROAD,
    WALL,
    UNREACHABLE
};

struct Cell {
    sf::RectangleShape rectangle;
    Point mapCoords;
    CellType cellType;
    bool isGhost;
};
