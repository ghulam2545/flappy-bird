#include "../include/texture.hpp"

namespace gh {
void texture::load() {
    // load all texture assets
    m_birds.assign(3, sf::Texture());
    m_birds[0].loadFromFile("../assets/flappy1.png");
    m_birds[1].loadFromFile("../assets/flappy2.png");
    m_birds[2].loadFromFile("../assets/flappy3.png");
    m_background.loadFromFile("../assets/background.png");
    m_pipe.loadFromFile("../assets/pipe.png");
    m_game_over.loadFromFile("../assets/gameover.png");
    m_title.loadFromFile("../assets/logo.png");
}
}  // namespace gh