#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"

int main() {
    GameMap gameMap;
    PacMan pacMan(12.5, 25, 25);
    GameWindow window(800, 600, "PAC-MAN GAME");
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