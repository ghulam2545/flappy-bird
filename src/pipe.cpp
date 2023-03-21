#include "../include/pipe.hpp"

namespace gh {
void pipe::load(gh::STATE& state, int frame_count,
                std::vector<sf::Sprite>& pipes) {
    gh::texture::load();
    if (state == gh::STATE::PLAYING && frame_count % 65 == 0) {
        int len = rand() % 275 + 75;
        int gap = 150;  // vertical gap between pipes

        // lower pipe
        m_lower_pipe.setTexture(gh::texture::m_pipe);
        m_lower_pipe.setPosition(1000, len + gap);
        m_lower_pipe.setScale(1, 2);

        // upper pipe
        m_upper_pipe.setTexture(gh::texture::m_pipe);
        m_upper_pipe.setPosition(1000, len);
        m_upper_pipe.setScale(1, -2);

        pipes.push_back(m_lower_pipe);
        pipes.push_back(m_upper_pipe);
    }
}

void pipe::move(gh::STATE& state, std::vector<sf::Sprite>& pipes) {
    if (state == gh::STATE::PLAYING) {
        for (auto& e : pipes) {
            e.move(-5, 0);  // maintain speed of pipes and horz gap
        }
    }
}

void pipe::erase(int frame_count, std::vector<sf::Sprite>& pipes) {
    if (frame_count % 100 == 0) {
        auto start = pipes.begin();
        auto end = pipes.begin();

        for (auto& e : pipes) {
            if (e.getPosition().x > -104) break;
        }
        pipes.erase(start, end);
    }
}

bool pipe::collision(std::vector<float>& lhs, std::vector<float>& rhs) {
    if (lhs[0] + lhs[2] >= rhs[0] && lhs[0] <= rhs[0] + rhs[2] &&
        lhs[1] + lhs[3] >= rhs[1] && lhs[1] <= rhs[1] + rhs[3])
        return true;
    return false;
}

}  // namespace gh