#include <SFML/Graphics.hpp>
#include <cassert>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"
#include "ghost.h"
#include "minimax.h"
#include "point.h"

static const std::string PACMAN_TEXTURE = "../resources/pacman.png";
static const std::vector<std::string> GHOST_TEXTURES = {"../resources/ghost-blue.png", "../resources/ghost-red.png",
                                                        "../resources/ghost-orange.png", "../resources/ghost-pink.png"};
static const char *LEVEL0_PATH_FILENAME = "../levels/level0.txt";
static const char *LEVEL1_PATH_FILENAME = "../levels/level1.txt";

int main() {
    GameMap gameMap(LEVEL1_PATH_FILENAME);
    const float blockSize = gameMap.getBlockSize();
    GameWindow window(gameMap.getWidth() * blockSize, gameMap.getHeight() * blockSize, "PAC-MAN GAME");
    PacMan pacMan(PACMAN_TEXTURE, {blockSize, blockSize},
                  gameMap.convertToWorldCoordinates(gameMap.getPacmanInitCoords()), 150.0f);
    std::deque<Ghost> ghosts; // use deque instead of vector because non-copyable and non-moveable reasons

    size_t i = 0;
    for (const Point& point : gameMap.getGhostsInitCoords()) {
        ghosts.emplace_back(GHOST_TEXTURES[i], sf::Vector2f{blockSize, blockSize},
                            gameMap.convertToWorldCoordinates(point), 150.0f);
        i = (i + 1) % GHOST_TEXTURES.size();
    }
    window.setGameMap(&gameMap);
    window.setPacMan(&pacMan);
    window.setGhosts(&ghosts);

    sf::Clock clock;

    bool lose = false;
    bool win = false;

    while (window.isOpen() && (!lose || !win)) {
        window.handleEvents();

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        pacMan.update(elapsedTime);
        for (Ghost& ghost : ghosts) {
            ghost.update(elapsedTime);
        }

//        if (pacMan.isWaiting()) {
//            auto to = gameMap.convertToWorldCoordinates(MiniMax::GetDecision(&pacMan, &ghosts[0], gameMap));
//            pacMan.setTarget(to);
//        }
//
//        if (ghosts[0].isWaiting()) {
//            auto to = gameMap.convertToWorldCoordinates(MiniMax::GetDecision(&ghosts[0], &pacMan, gameMap));
//            ghosts[0].setTarget(to);
//        }
//
//        if (ghosts[1].isWaiting()) {
//            auto to = gameMap.convertToWorldCoordinates(MiniMax::GetDecision(&ghosts[1], &pacMan, gameMap));
//            ghosts[1].setTarget(to);
//        }

        if (gameMap.checkPacmanAtCookie(&pacMan)) {
            pacMan.eatCookie();
            std::cout << "Omnomnom\n";
            if (gameMap.getCookies().empty()) {
                win = true;
            }
        }

        window.render();

        for (const Ghost& ghost : ghosts) {
            if (ghost.getGlobalBounds().intersects(pacMan.getGlobalBounds())) {
                lose = true;
                break;
            }
        }
    }

    assert(!(lose & win)); // assert for both lose and win situation

    if (lose) {
        std::cout << "PACMAN LOSE\n";
    } else if (win) {
        std::cout << "PACMAN WON\n";
    } else {
        std::cout << "EXIT\n";
    }
    std::cout << "Pacman has eaten " << pacMan.getCookieCount() << " fruits\n";

    return 0;
}