#include <SFML/Graphics.hpp>
#include <ctime>

#include "./include/bird.hpp"
#include "./include/game.hpp"
#include "./include/pipe.hpp"
#include "./include/sound.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "flappy-bird");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    srand(time(0));

    gh::sound sound;
    sound.load();

    gh::bird bird;
    bird.load();

    gh::pipe pipe;
    std::vector<sf::Sprite> allPipes;

    gh::game app;
    app.load();

    while (window.isOpen()) {
        bird.update(app.m_state,
                    app.m_frame_count);  // drop bird and update wings

        // game over, if it hits ground
        auto currPos = bird.get_pos();
        if (app.m_state == gh::STATE::PLAYING) {
            if (currPos[1] < 0) {
                bird.m_sprite.setPosition(250, 0);
                bird.m_speed = 0;
            }
            if (currPos[1] > 600) {
                bird.m_speed = 0;
                app.m_state = gh::STATE::GAME_OVER;
                sound.play_hit();
            }
        }

        // pipe working
        pipe.load(app.m_state, app.m_frame_count, allPipes);
        pipe.move(app.m_state, allPipes);
        pipe.erase(app.m_frame_count, allPipes);

        // add up score
        for (auto& e : allPipes) {
            if (app.m_state == gh::STATE::PLAYING && e.getPosition().x == 250) {
                ++app.m_score;
                sound.play_score();

                if (app.m_score > app.m_high_score) {
                    app.m_high_score = app.m_score;
                }
                break;
            }
        }

        // checking for collision
        if (app.m_state == gh::STATE::PLAYING) {
            std::vector<float> pos(4);
            for (auto& e : allPipes) {
                if (e.getScale().y > 0) {
                    pos[0] = e.getPosition().x;
                    pos[1] = e.getPosition().y;
                    pos[2] = 52 * e.getScale().x;
                    pos[3] = 320 * e.getScale().y;
                } else {
                    pos[2] = 52 * e.getScale().x;
                    pos[3] = -320 * e.getScale().y;
                    pos[0] = e.getPosition().x;
                    pos[1] = e.getPosition().y - pos[3];
                }
                if (pipe.collision(currPos, pos)) {
                    bird.m_speed = 0;
                    app.m_state = gh::STATE::GAME_OVER;
                    sound.play_hit();
                }
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed &&
                       event.key.code == sf::Keyboard::Space) {
                if (app.m_state == gh::STATE::NOT_PLAYING) {
                    app.m_state = gh::STATE::PLAYING;
                }
                if (app.m_state == gh::STATE::PLAYING) {
                    bird.m_speed = -8;
                    sound.play_fly();
                }
            } else if (event.type == sf::Event::KeyPressed &&
                       event.key.code == sf::Keyboard::Escape &&
                       app.m_state == gh::STATE::GAME_OVER) {
                app.m_state = gh::STATE::PLAYING;
                bird.load();
                app.m_score = 0;
                allPipes.clear();
            }
        }

        window.clear();

        app.draw_background(window);
        if (app.m_state == gh::STATE::NOT_PLAYING) {
            app.draw_title(window);
        }

        for (auto& e : allPipes) window.draw(e);
        bird.draw(window);
        app.draw_score(window);
        if (app.m_state == gh::STATE::GAME_OVER) {
            app.draw_gameover(window);
        }

        window.display();
        app.m_frame_count += 1;
    }

    return 0;
}