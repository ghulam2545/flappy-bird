#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Flappy Bird");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // close the window
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}