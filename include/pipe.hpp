#ifndef PIPE_HPP
#define PIPE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "texture.hpp"

namespace gh {
class pipe : protected texture {
   public:
    void load(gh::STATE& state, int frame_count,
              std::vector<sf::Sprite>& pipes);
    void move(gh::STATE& state, std::vector<sf::Sprite>& pipes);
    void erase(int frame_count, std::vector<sf::Sprite>& pipes);
    bool collision(std::vector<float>& lhs, std::vector<float>& rhs);

   private:
    sf::Sprite m_lower_pipe;
    sf::Sprite m_upper_pipe;
};
}  // namespace gh

#endif