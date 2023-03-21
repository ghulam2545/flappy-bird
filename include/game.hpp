#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "texture.hpp"

namespace gh {
enum STATE { PLAYING, NOT_PLAYING, GAME_OVER };

class game : protected texture {
   public:
    game();
    void load();
    void draw_background(sf::RenderWindow& window);
    void draw_title(sf::RenderWindow& window);
    void draw_gameover(sf::RenderWindow& window);
    void draw_score(sf::RenderWindow& window);

    int m_frame_count;
    STATE m_state;
    int m_score;
    int m_high_score;

   private:
    std::vector<sf::Sprite> m_background;
    sf::Sprite m_game_over;
    sf::Sprite m_title;

    sf::Text m_score_text;
    sf::Text m_high_score_text;
    sf::Text m_continue_text;
    sf::Text m_start_text;

    sf::Font m_font;
};
}  // namespace gh

#endif