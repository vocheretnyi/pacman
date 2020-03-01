#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"

std::string PACMAN_TEXTURE = "/home/vocheretnyi/CLionProjects/pac-man/resources/pacman.png";

int main() {
    GameMap gameMap;
    PacMan pacMan(PACMAN_TEXTURE, 12.5, 50, 50);
    GameWindow window(625, 625, "PAC-MAN GAME");
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