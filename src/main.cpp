#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"

std::string PACMAN_TEXTURE = "/home/vocheretnyi/CLionProjects/pac-man/resources/pacman.png";

int main() {
    GameMap gameMap;
    PacMan pacMan(PACMAN_TEXTURE,  gameMap.getBlockSize() / 2.0, 50, 50);
    GameWindow window(gameMap.getWidth() * gameMap.getBlockSize(), gameMap.getHeight() * gameMap.getBlockSize(), "PAC-MAN GAME");
    window.setGameMap(&gameMap);
    window.setPacMan(&pacMan);

    sf::Clock clock;

    while (window.isOpen()) {
        window.handleEvents();

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        pacMan.update(elapsedTime);

        window.render();
    }

    return 0;
}