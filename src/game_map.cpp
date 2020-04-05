#include "game_map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <cassert>

#include "path_finder.h"
#include "point.h"
#include "pacman.h"

using namespace std;

static const sf::Color WALL_COLOR = sf::Color(52, 93, 199);
static const sf::Color ROAD_COLOR = sf::Color(40, 40, 40);

static const char WALL_MARKER = '#';
static const char UNREACHABLE_MARKER = '!';
static const char ROAD_MARKER = ' ';
static const char COOKIE_MARKER = '.';
static const char PACMAN_MARKER = '$';
static const char GHOST_MARKER = '@';

const vector<Point> neighboursDeltas = {{-1, 0},
                                        {0,  -1},
                                        {1,  0},
                                        {0,  1}};

static const std::string cookieTextureName = "../resources/fruit.png";

static const sf::Color& getCorrectColor(CellType cellType) {
    switch (cellType) {
        case CellType::COOKIE:
        case CellType::UNREACHABLE:
        case CellType::ROAD:
            return ROAD_COLOR;;
        case CellType::WALL:
            return WALL_COLOR;
        default:
            assert(false);
    }
}

static CellType GetCellType(char ch) {
    switch (ch) {
        case WALL_MARKER:
            return CellType::WALL;
        case UNREACHABLE_MARKER:
            return CellType::UNREACHABLE;
        case ROAD_MARKER:
        case PACMAN_MARKER:
        case GHOST_MARKER:
            return CellType::ROAD;
        case COOKIE_MARKER:
            return CellType::COOKIE;
        default:
            assert(false);
            return CellType::UNREACHABLE;
    }
}

GameMap::GameMap(const string& mapFilePathName) {
    ifstream in(mapFilePathName);
    in >> width >> height;
    in.ignore();
    std::vector<std::string> fieldMaze;
    fieldMaze.resize(height);
    for (string& line : fieldMaze) {
        getline(in, line);
    }

    cookieTexture.loadFromFile(cookieTextureName);

    visited = vector<vector<double>>(width, vector<double>(height, 0.0f));

    cells.resize(width);
    for (int x = 0; x < width; ++x) {
        cells[x].resize(height);
        for (int y = 0; y < height; ++y) {
            const Point point = {x, y};
            Cell& cell = cells[x][y];
            cell.cellType = GetCellType(fieldMaze[y][x]);
            cell.rectangle = sf::RectangleShape(sf::Vector2f{kBlockSize, kBlockSize});
            cell.rectangle.setPosition(x * kBlockSize, y * kBlockSize);
            cell.rectangle.setFillColor(getCorrectColor(cell.cellType));
            cell.mapCoords = point;

            if (fieldMaze[y][x] == GHOST_MARKER) {
                ghostsInitCoords.push_back(point);
            }

            if (fieldMaze[y][x] == PACMAN_MARKER) {
                pacmanInitCoords = point;
            }

            if (isCookie(point)) {
                cookies.push_back(cell.rectangle);
                cookies.back().setFillColor(sf::Color::White); // TODO: need this lines because of bug with texture
                cookies.back().setTexture(&cookieTexture);
            }
        }
    }
}

size_t GameMap::getWidth() const {
    return width;
}

size_t GameMap::getHeight() const {
    return height;
}

float GameMap::getBlockSize() const {
    return kBlockSize;
}

const vector<vector<Cell>>& GameMap::getCells() const {
    return cells;
}

const vector<sf::RectangleShape>& GameMap::getCookies() const {
    return cookies;
}

queue<sf::Vector2f> GameMap::createWayTo(const sf::Vector2f& to, const sf::Vector2f& from) const {
    Point fn = convertToMapCoordinates(to);
    Point st = convertToMapCoordinates(from);

//    auto res1 = ConvertWayToWorldCoordinates(PathFinder::dfs(st, fn, *this));
//    auto res2 = ConvertWayToWorldCoordinates(PathFinder::bfs(st, fn, *this));
//    auto res3 = ConvertWayToWorldCoordinates(PathFinder::greedy(st, fn, *this));
    auto res4 = ConvertWayToWorldCoordinates(PathFinder::a_star(st, fn, *this));

    return res4;
}

std::vector<Point> GameMap::getNeighbours(const Point& cur, bool isForGhost) const {
    std::vector<Point> res;
    for (const Point& delta : neighboursDeltas) {
        Point to = cur + delta;
        if (canGoTo(to)) {
            if (isForGhost && cells[to.x][to.y].isGhost) {
                continue;
            }
            res.push_back(to);
        }
    }
    return res;
}

queue<sf::Vector2f> GameMap::ConvertWayToWorldCoordinates(const vector<Point>& way) const {
    queue<sf::Vector2f> convertedWay;
    for (const auto& point : way) {
        convertedWay.push(convertToWorldCoordinates(point));
    }
    return convertedWay;
}

Point GameMap::convertToMapCoordinates(const sf::Vector2f& p) const {
    return {static_cast<int>(p.x / kBlockSize), static_cast<int>(p.y / kBlockSize)};
}

sf::Vector2f GameMap::convertToWorldCoordinates(const Point& p) const {
    return {p.x * kBlockSize, p.y * kBlockSize};
}

bool GameMap::canGoTo(const Point& p) const {
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height && (isRoad(p) || isCookie(p));
}

//bool GameMap::checkPacmanAtCookie(const Monster *pacman) {
//    Point pacmanCoord = convertToMapCoordinates(pacman->getPosition());
//    if (isCookie(pacmanCoord)) {
//        eatCookie(pacmanCoord);
//        return true;
//    }
//    return false;
//}

void GameMap::eatCookie(const Point& p) {
    assert(cells[p.x][p.y].cellType == CellType::COOKIE);
    cells[p.x][p.y].cellType = CellType::ROAD;
    cookies.erase(
            std::find_if(cookies.begin(), cookies.end(), [&](const sf::RectangleShape& rect) {
                return convertToMapCoordinates(rect.getPosition()) == p;
            })
    );
}

bool GameMap::isWall(const Point& p) const {
    return cells[p.x][p.y].cellType == CellType::WALL;
}

bool GameMap::isCookie(const Point& p) const {
    return cells[p.x][p.y].cellType == CellType::COOKIE;
}

bool GameMap::isRoad(const Point& p) const {
    return cells[p.x][p.y].cellType == CellType::ROAD;
}

const Point& GameMap::getPacmanInitCoords() const {
    return pacmanInitCoords;
}

const std::vector<Point>& GameMap::getGhostsInitCoords() const {
    return ghostsInitCoords;
}

void GameMap::setGhostsPositions(std::vector<Point> ghostsPos, bool value) {
    for (const Point& point : ghostsPos) {
        cells[point.x][point.y].isGhost = value;
    }
}
