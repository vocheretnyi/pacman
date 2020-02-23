#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"
#include "game_map.h"

int main() {
    GameWindow window(800, 600, "PAC-MAN GAME");
    PacMan pacMan(12.5);
    GameMap gameMap;
    sf::Clock clock;

    while (window.isOpen()) {
        window.handleEvents(pacMan);

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        pacMan.update(elapsedTime);

        window.render(pacMan, gameMap);
    }

    return 0;
}