#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "texture.hpp"

namespace gh {
class bird : protected texture {
   public:
    bird();
    void load();
    void draw(sf::RenderWindow& window);
    void update(gh::STATE& state, int& frame_count);
    std::vector<float> get_pos();

    sf::Sprite m_sprite;
    double m_speed;
    int m_bird_frame_count;
};
}  // namespace gh

#endif