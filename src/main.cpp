#include <SFML/Graphics.hpp>
#include <cassert>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"
#include "ghost.h"
#include "ghostController.h"
#include "point.h"
#include "pacmanController.h"

using namespace std;

static const std::string PACMAN_TEXTURE = "../resources/pacman.png";
static const std::vector<std::string> GHOST_TEXTURES = {"../resources/ghost-blue.png", "../resources/ghost-red.png",
                                                        "../resources/ghost-orange.png", "../resources/ghost-pink.png"};
static const char *LEVEL1_PATH_FILENAME = "../levels/level1.txt";
static const char *LEVEL2_PATH_FILENAME = "../levels/level2.txt";

static const char *LEVELS_PATH = "../levels/level";

static vector<Point> getGhostsPos(const deque<Ghost>& ghosts, const GameMap& gameMap) {
    vector<Point> res;
    for (const Ghost& ghost : ghosts) {
        res.push_back(gameMap.convertToMapCoordinates(ghost.getPosition()));
    }
    return res;
}

void startGame(int level) {
    if (level > 3) {
        return;
    }
    GameMap gameMap(LEVELS_PATH + to_string(level) + ".txt");
    const float blockSize = gameMap.getBlockSize();
    GameWindow window(gameMap.getWidth() * blockSize, gameMap.getHeight() * blockSize, "PAC-MAN GAME");
    PacMan pacMan(PACMAN_TEXTURE, {blockSize, blockSize},
                  gameMap.convertToWorldCoordinates(gameMap.getPacmanInitCoords()), 300.0f);
    std::deque<Ghost> ghosts; // use deque instead of vector because non-copyable and non-moveable reasons

    size_t i = 0;
    // 3 - 50
    // 2 - 75
    // 1 - 100
    double val = (5 - gameMap.getGhostsInitCoords().size()) * 25.0;
    for (const Point& point : gameMap.getGhostsInitCoords()) {
        ghosts.emplace_back(GHOST_TEXTURES[i], sf::Vector2f{blockSize, blockSize},
                            gameMap.convertToWorldCoordinates(point), val * (i + 1));
        i = (i + 1) % GHOST_TEXTURES.size();
    }
    window.setGameMap(&gameMap);
    window.setPacMan(&pacMan);
    window.setGhosts(&ghosts);

    sf::Clock clock;

    bool lose = false;
    bool win = false;

    int cookiesCnt = gameMap.getCookies().size();


    while (window.isOpen() && (!lose && !win)) {
        window.handleEvents();

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        window.setTitle("PAC-MAN GAME | Fruits: " + to_string(pacMan.getCookieCount()) + "/" + to_string(cookiesCnt) + " | Level: " + to_string(level));

        pacMan.update(elapsedTime);
        for (Ghost& ghost : ghosts) {
            ghost.update(elapsedTime);
        }

        for (int i = 0; i < ghosts.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (ghosts[i].getGlobalBounds().intersects(ghosts[j].getGlobalBounds())) {
                    ghosts[j].stopMoving();
                }
            }
        }

        for (const Ghost& ghost : ghosts) {
            if (ghost.getGlobalBounds().intersects(pacMan.getGlobalBounds())) {
                lose = true;
                break;
            }
        }

        auto& visited = gameMap.visited;
        for (int x = 0; x < visited.size(); ++x) {
            for (int y = 0; y < visited[x].size(); ++y) {
                visited[x][y] *= 0.95;
            }
        }

        if (pacMan.isWaiting()) {
//            auto to = gameMap.convertToWorldCoordinates(MiniMax::GetDecision(&pacMan, &ghosts[0], gameMap));
            auto to = gameMap.convertToWorldCoordinates(PacManController::GetDecision(pacMan, ghosts, gameMap));
            pacMan.setTarget(to);
        }

        Point pacManPos = gameMap.convertToMapCoordinates(pacMan.getPosition());
        visited[pacManPos.x][pacManPos.y] += 1;

        gameMap.setGhostsPositions(getGhostsPos(ghosts, gameMap), true);
        for (Ghost& ghost : ghosts) {
            if (ghost.isWaiting()) {
                auto to = gameMap.convertToWorldCoordinates(GhostController::GetDecision(pacMan, ghost, gameMap));
                ghost.setTarget(to);
            }
        }

        if (gameMap.isCookie(gameMap.convertToMapCoordinates(pacMan.getPosition()))) {
            gameMap.eatCookie(gameMap.convertToMapCoordinates(pacMan.getPosition()));
            pacMan.eatCookie();
//            std::cout << "Omnomnom\n";
            if (gameMap.getCookies().empty()) {
                win = true;
            }
        }

        gameMap.setGhostsPositions(getGhostsPos(ghosts, gameMap), false);

        window.render();
    }

    assert(!(lose & win)); // assert for both lose and win situation

    if (lose) {
        std::cout << "PACMAN LOSE\n";
    } else if (win) {
        std::cout << "PACMAN WON Level " << level << "\n";
        startGame(level + 1);
    } else {
        std::cout << "EXIT\n";
    }
    std::cout << "Pacman has eaten " << pacMan.getCookieCount() << " fruits\n";
}

int main() {
    startGame(3);

    return 0;
}