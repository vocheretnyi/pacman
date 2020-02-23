#include <SFML/Graphics.hpp>

#include "pacman.h"
#include "game_window.h"

int main() {
    GameWindow window(900, 600, "PAC-MAN GAME");
    PacMan pacMan(40.0);
    sf::Clock clock;
    while (window.isOpen()) {
        window.handleEvents(pacMan);

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        pacMan.update(elapsedTime);

        window.render(pacMan);
    }

    return 0;
}