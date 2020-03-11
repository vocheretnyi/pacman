#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"
#include "ghost.h"
#include "minimax.h"
#include "point.h"

static const char* PACMAN_TEXTURE = "../resources/pacman.png";
static const char* GHOST_TEXTURE = "../resources/ghost-blue.png";
static const char* LEVEL0_PATH_FILENAME = "../levels/level0.txt";
static const char* LEVEL1_PATH_FILENAME = "../levels/level1.txt";

int main() {
    GameMap gameMap(LEVEL1_PATH_FILENAME);
    GameWindow window(gameMap.getWidth() * gameMap.getBlockSize(), gameMap.getHeight() * gameMap.getBlockSize(), "PAC-MAN GAME");
    PacMan pacMan(PACMAN_TEXTURE,  gameMap.getBlockSize() / 2.0, 7 * 25, 3 * 25);
    Ghost ghost(GHOST_TEXTURE, {gameMap.getBlockSize(), gameMap.getBlockSize()}, 50, 75);
    window.setGameMap(&gameMap);
    window.setPacMan(&pacMan);
    window.setGhost(&ghost);

    sf::Clock clock;

    bool lose = false;

    while (window.isOpen()) {
        window.handleEvents();

        if (lose) {
            continue;
        }

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        pacMan.update(elapsedTime);
        ghost.update(elapsedTime);

        if (ghost.isWaiting()) {
            auto to = gameMap.convertToWorldCoordinates(MiniMax::GetDecision(ghost, pacMan, gameMap));
            ghost.setTarget(to);
        }

        window.render();

        if (ghost.getGlobalBounds().intersects(pacMan.getGlobalBounds())) {
            lose = true;
        }
    }

    if (lose) {
        std::cout << "PACMAN LOSE\n";
    }

    return 0;
}