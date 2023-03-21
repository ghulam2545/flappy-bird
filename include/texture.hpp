#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>

namespace gh {
class texture {
   public:
    void load();
    sf::Texture m_pipe;

   protected:
    std::vector<sf::Texture> m_birds;
    sf::Texture m_background;
    sf::Texture m_game_over;
    sf::Texture m_title;
};
}  // namespace gh

#endif