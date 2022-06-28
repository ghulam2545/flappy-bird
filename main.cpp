/**
 * @file main.cpp
 * @author ghulam mustafa (ghulam2545@gmail.com)
 * @brief Flappy Bird is a mobile game developed by Vietnamese video game artist and programmer Dong Nguyen. This is the same, cloned
 *        with the help of c++ and SFML library.
 * @version 0.1
 * @date 2022-06-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <vector>

namespace gh {

    // forward declation of the classes
    class Sound;    // organising sound related things
    class Texture;  // organising sound related things
    class Bird;     // organising sound related things
    class Pipe;     // organising sound related things
    class Game;     // organising sound related things

    class Sound {
       public:
        void load();
        void playScore();
        void playHit();
        void playFly();

       private:
        sf::SoundBuffer scoreBuffer;
        sf::SoundBuffer flyBuffer;
        sf::SoundBuffer hitBuffer;
        sf::Sound scoreSound;
        sf::Sound flySound;
        sf::Sound hitSound;
    };

    class Texture {
       public:
        void load();
        sf::Texture pipe;

       protected:
        std::vector<sf::Texture> birds;
        sf::Texture background;
        sf::Texture gameOver;
        sf::Texture title;
    };

    enum GameState { playing, not_playing, game_over };

    class Bird : protected Texture {
       public:
        Bird() : speed(0.0), birdFrameCount(0) {}
        void load();
        void draw(sf::RenderWindow& window);
        void update(gh::GameState& state, int& gameFrameCount);
        std::vector<float> getPos();

        sf::Sprite sprite;
        double speed;
        int birdFrameCount;
    };

    class Pipe : protected Texture {
       public:
        void load(gh::GameState& state, int gameFrameCount, std::vector<sf::Sprite>& pipes);
        void move(gh::GameState& state, std::vector<sf::Sprite>& pipes);
        void erase(int gameFrameCount, std::vector<sf::Sprite>& pipes);
        bool collision(std::vector<float>& one, std::vector<float>& two);

       private:
        sf::Sprite lowerPipe;
        sf::Sprite upperPipe;
    };

    class Game : protected Texture {
       public:
        Game() : score(0), highScore(0), gameFrameCount(0), state(not_playing) {}
        void load();
        void drawBackground(sf::RenderWindow& window);
        void drawTitle(sf::RenderWindow& window);
        void drawGameOver(sf::RenderWindow& window);
        void drawScore(sf::RenderWindow& window);

        int gameFrameCount;
        GameState state;
        int score;
        int highScore;

       private:
        std::vector<sf::Sprite> background;
        sf::Sprite gameOver;
        sf::Sprite title;

        sf::Text scoreText;
        sf::Text highScoreText;
        sf::Text continueText;
        sf::Text startText;

        sf::Font font;
    };

}  // namespace gh

////////////////////////////////////////////////////////////////////
// start of main
////////////////////////////////////////////////////////////////////

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Flappy Bird");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    srand(time(0));

    gh::Sound sound;
    sound.load();

    gh::Bird bird;
    bird.load();

    gh::Pipe pipe;
    std::vector<sf::Sprite> allPipes;

    gh::Game app;
    app.load();

    while (window.isOpen()) {
        bird.update(app.state, app.gameFrameCount);  // drop bird and update wings

        // game over if hits ground
        auto currPos = bird.getPos();
        if (app.state == gh::playing) {
            if (currPos[1] < 0) {
                bird.sprite.setPosition(250, 0);
                bird.speed = 0;
            }
            if (currPos[1] > 600) {
                bird.speed = 0;
                app.state = gh::game_over;
                sound.playHit();
            }
        }

        // pipe working
        pipe.load(app.state, app.gameFrameCount, allPipes);
        pipe.move(app.state, allPipes);
        pipe.erase(app.gameFrameCount, allPipes);

        // add up score
        for (auto& e : allPipes) {
            if (app.state == gh::playing && e.getPosition().x == 250) {
                ++app.score;
                sound.playScore();

                if (app.score > app.highScore) {
                    app.highScore = app.score;
                }
                break;
            }
        }

        // checking for collision
        if (app.state == gh::playing) {
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
                    bird.speed = 0;
                    app.state = gh::game_over;
                    sound.playHit();
                }
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // please close the window
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (app.state == gh::not_playing) {
                    app.state = gh::playing;
                }
                if (app.state == gh::playing) {
                    bird.speed = -8;
                    sound.playFly();
                }
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && app.state == gh::game_over) {
                app.state = gh::playing;
                bird.load();
                app.score = 0;
                allPipes.clear();
            }
        }

        window.clear();

        app.drawBackground(window);
        if (app.state == gh::not_playing) {
            app.drawTitle(window);
        }

        for (auto& e : allPipes) window.draw(e);
        bird.draw(window);
        app.drawScore(window);
        if (app.state == gh::game_over) {
            app.drawGameOver(window);
        }

        window.display();

        app.gameFrameCount += 1;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////
// end of main
////////////////////////////////////////////////////////////////////

namespace gh {

    void Sound::load() {
        // here we are loading all required sounds
        scoreBuffer.loadFromFile("./assets/score.wav");
        flyBuffer.loadFromFile("./assets/fly.wav");
        hitBuffer.loadFromFile("./assets/hit.wav");
        scoreSound.setBuffer(scoreBuffer);
        flySound.setBuffer(flyBuffer);
        hitSound.setBuffer(hitBuffer);
    }

    void Sound::playScore() { scoreSound.play(); }

    void Sound::playHit() { hitSound.play(); }

    void Sound::playFly() { flySound.play(); }

    void Texture::load() {
        // here we are loading all required picture
        birds.assign(3, sf::Texture());
        birds[0].loadFromFile("./assets/flappy1.png");
        birds[1].loadFromFile("./assets/flappy2.png");
        birds[2].loadFromFile("./assets/flappy3.png");
        background.loadFromFile("./assets/background.png");
        pipe.loadFromFile("./assets/pipe.png");
        gameOver.loadFromFile("./assets/gameover.png");
        title.loadFromFile("./assets/logo.png");
    }

    void Bird::load() {
        sprite.setPosition(250, 310);
        sprite.setScale(1.6, 1.6);
    }

    void Bird::draw(sf::RenderWindow& window) { window.draw(sprite); }

    void Bird::update(gh::GameState& state, int& gameFrameCount) {
        gh::Texture::load();
        sprite.setTexture(birds[0]);

        if (state == gh::playing) {
            if (gameFrameCount % 2 == 0) {
                ++birdFrameCount;
            }
            if (birdFrameCount == 3) {
                birdFrameCount = 0;
            }
        }

        sprite.setTexture(birds[birdFrameCount]);

        if (state == gh::playing) {
            sprite.move(0, speed);
            speed += 0.5;
        }
    }

    std::vector<float> Bird::getPos() {
        auto x = sprite.getPosition().x;
        auto y = sprite.getPosition().y;
        auto width = 34 * sprite.getScale().x;
        auto height = 24 * sprite.getScale().y;

        std::vector<float> res = {x, y, width, height};
        return res;
    }

    void Pipe::load(gh::GameState& state, int gameFrameCount, std::vector<sf::Sprite>& pipes) {
        gh::Texture::load();
        if (state == gh::playing && gameFrameCount % 60 == 0) {
            int len = rand() % 275 + 75;
            int gap = 150;  // vertical gap between pipes

            // lower pipe
            lowerPipe.setTexture(gh::Texture::pipe);
            lowerPipe.setPosition(1000, len + gap);
            lowerPipe.setScale(1, 2);

            // upper pipe
            upperPipe.setTexture(gh::Texture::pipe);
            upperPipe.setPosition(1000, len);
            upperPipe.setScale(1, -2);

            pipes.push_back(lowerPipe);
            pipes.push_back(upperPipe);
        }
    }

    void Pipe::move(gh::GameState& state, std::vector<sf::Sprite>& pipes) {
        if (state == gh::playing) {
            for (auto& e : pipes) {
                e.move(-5.5, 0);  // maintain speed of pipes and horz gap
            }
        }
    }

    void Pipe::erase(int gameFrameCount, std::vector<sf::Sprite>& pipes) {
        if (gameFrameCount % 100 == 0) {
            auto start = pipes.begin();
            auto end = pipes.begin();

            for (auto& e : pipes) {
                if (e.getPosition().x > -104) break;
            }
            pipes.erase(start, end);
        }
    }

    bool Pipe::collision(std::vector<float>& one, std::vector<float>& two) {
        if (one[0] + one[2] >= two[0] && one[0] <= two[0] + two[2] && one[1] + one[3] >= two[1] && one[1] <= two[1] + two[3]) return true;
        return false;
    }

    void Game::load() {
        font.loadFromFile("./assets/flappy.ttf");

        gh::Texture::load();
        this->background.assign(3, sf::Sprite());
        for (int i = 0; i < 3; ++i) {
            this->background[i].setTexture(gh::Texture::background);
            this->background[i].setScale(1.15625, 1.171875);
        }
        this->background[1].setPosition(333, 0);
        this->background[2].setPosition(666, 0);

        this->title.setTexture(gh::Texture::title);
        this->title.setPosition(250, 110);

        this->gameOver.setTexture(gh::Texture::gameOver);
        this->gameOver.setPosition(280, 150);
        this->gameOver.setScale(1.8, 1.8);

        scoreText.setFont(font);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setCharacterSize(35);
        scoreText.setPosition(15, 10);

        highScoreText.setFont(font);
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setCharacterSize(25);
        highScoreText.setPosition(15, 55);

        startText.setFont(font);
        startText.setFillColor(sf::Color::White);
        startText.setCharacterSize(35);
        startText.setString("Press SPACE to play.");
        startText.setPosition(270, 230);

        continueText.setFont(font);
        continueText.setFillColor(sf::Color::White);
        continueText.setCharacterSize(35);
        continueText.setString("Press ESC to continue.");
        continueText.setPosition(260, 250);
    }

    void Game::drawBackground(sf::RenderWindow& window) {
        for (int i = 0; i < 3; ++i) {
            window.draw(this->background[i]);
        }
    }

    void Game::drawTitle(sf::RenderWindow& window) {
        window.draw(this->title);
        window.draw(startText);
    }

    void Game::drawGameOver(sf::RenderWindow& window) {
        window.draw(this->gameOver);
        window.draw(this->continueText);
    }

    void Game::drawScore(sf::RenderWindow& window) {
        scoreText.setString("SCORE : " + std::to_string(score));
        highScoreText.setString("HIGH SCORE : " + std::to_string(highScore));
        window.draw(scoreText);
        window.draw(highScoreText);
    }

}  // namespace gh