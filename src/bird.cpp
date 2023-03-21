#include "../include/bird.hpp"

namespace gh {
bird::bird() {}

void bird::load() {
    m_sprite.setPosition(250, 310);
    m_sprite.setScale(1.6, 1.6);
}

void bird::draw(sf::RenderWindow& window) { window.draw(m_sprite); }

void bird::update(gh::STATE& state, int& frame_count) {
    gh::texture::load();
    m_sprite.setTexture(m_birds[0]);

    if (state == gh::STATE::PLAYING) {
        if (frame_count % 2 == 0) {
            ++m_bird_frame_count;
        }
        if (m_bird_frame_count == 3) {
            m_bird_frame_count = 0;
        }
    }

    m_sprite.setTexture(m_birds[m_bird_frame_count]);

    if (state == gh::STATE::PLAYING) {
        m_sprite.move(0, m_speed);
        m_speed += 0.5;
    }
}

std::vector<float> bird::get_pos() {
    auto x = m_sprite.getPosition().x;
    auto y = m_sprite.getPosition().y;
    auto width = 34 * m_sprite.getScale().x;
    auto height = 24 * m_sprite.getScale().y;

    std::vector<float> res = {x, y, width, height};
    return res;
}

}  // namespace gh