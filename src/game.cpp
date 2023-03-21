#include "../include/game.hpp"

namespace gh {
game::game()
    : m_score{0},
      m_high_score{0},
      m_frame_count{0},
      m_state{STATE::NOT_PLAYING} {}

void game::load() {
    m_font.loadFromFile("../assets/flappy.ttf");

    gh::texture::load();
    this->m_background.assign(3, sf::Sprite());
    for (int i = 0; i < 3; ++i) {
        this->m_background[i].setTexture(gh::texture::m_background);
        this->m_background[i].setScale(1.15625, 1.171875);
    }
    this->m_background[1].setPosition(333, 0);
    this->m_background[2].setPosition(666, 0);

    this->m_title.setTexture(gh::texture::m_title);
    this->m_title.setPosition(250, 110);

    this->m_game_over.setTexture(gh::texture::m_game_over);
    this->m_game_over.setPosition(280, 150);
    this->m_game_over.setScale(1.8, 1.8);

    m_score_text.setFont(m_font);
    m_score_text.setFillColor(sf::Color::White);
    m_score_text.setCharacterSize(35);
    m_score_text.setPosition(15, 10);

    m_high_score_text.setFont(m_font);
    m_high_score_text.setFillColor(sf::Color::White);
    m_high_score_text.setCharacterSize(25);
    m_high_score_text.setPosition(15, 55);

    m_start_text.setFont(m_font);
    m_start_text.setFillColor(sf::Color::White);
    m_start_text.setCharacterSize(35);
    m_start_text.setString("Press SPACE to play.");
    m_start_text.setPosition(270, 230);

    m_continue_text.setFont(m_font);
    m_continue_text.setFillColor(sf::Color::White);
    m_continue_text.setCharacterSize(35);
    m_continue_text.setString("Press ESC to continue.");
    m_continue_text.setPosition(260, 250);
}

void game::draw_background(sf::RenderWindow& window) {
    for (int i = 0; i < 3; ++i) {
        window.draw(m_background[i]);
    }
}

void game::draw_title(sf::RenderWindow& window) {
    window.draw(m_title);
    window.draw(m_start_text);
}

void game::draw_gameover(sf::RenderWindow& window) {
    window.draw(m_game_over);
    window.draw(m_continue_text);
}

void game::draw_score(sf::RenderWindow& window) {
    m_score_text.setString("SCORE : " + std::to_string(m_score));
    m_high_score_text.setString("HIGH SCORE : " + std::to_string(m_high_score));
    window.draw(m_score_text);
    window.draw(m_high_score_text);
}

}  // namespace gh