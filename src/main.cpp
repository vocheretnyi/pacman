#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"
#include "ghost.h"
#include "minimax.h"
#include "point.h"

static const char *PACMAN_TEXTURE = "../resources/pacman.png";
static const char *GHOST_TEXTURE = "../resources/ghost-blue.png";
static const char *LEVEL0_PATH_FILENAME = "../levels/level0.txt";
static const char *LEVEL1_PATH_FILENAME = "../levels/level1.txt";

int main() {
    GameMap gameMap(LEVEL1_PATH_FILENAME);
    const float blockSize = gameMap.getBlockSize();
    GameWindow window(gameMap.getWidth() * blockSize, gameMap.getHeight() * blockSize, "PAC-MAN GAME");
    PacMan pacMan(PACMAN_TEXTURE, {blockSize, blockSize}, gameMap.convertToWorldCoordinates({7, 3}));
    Ghost ghost(GHOST_TEXTURE, {blockSize, blockSize}, gameMap.convertToWorldCoordinates({2, 3}));
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

        if (gameMap.checkPacmanAtCookie(pacMan)) {
            pacMan.eatCookie();
            std::cout << "OMM\n";
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