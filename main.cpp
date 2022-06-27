#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <vector>

namespace gh {

    // forward declation of the classes
    class Sound;
    class Texture;
    class Bird;
    class Game;

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

       protected:
        std::vector<sf::Texture> birds;
        sf::Texture background;
        sf::Texture pipe;
        sf::Texture gameOver;
        sf::Texture title;
    };

    class Bird : protected Texture {
       public:
        void load() {
            sprite.setPosition(250, 300);
            sprite.setScale(1.8, 1.8);
        }

        void draw(sf::RenderWindow& window) { window.draw(sprite); }
        void update(int whichOne) {
            gh::Texture::load();
            sprite.setTexture(birds[whichOne]);
            sprite.setPosition(250, 320);
            sprite.setScale(1.6, 1.6);
        }

        sf::Sprite sprite;
        double speed;
        int birdFrameCount = 0;
    };

    enum GameState { playing, not_playing, game_over };

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

    gh::Game app;
    app.load();

    while (window.isOpen()) {
        bird.update(0);

        if (app.gameFrameCount % 6 == 0) {
            ++bird.birdFrameCount;
        }
        if (bird.birdFrameCount == 3) {
            bird.birdFrameCount = 0;
        }

        bird.update(bird.birdFrameCount);

        // TODO:..................................
        // if (app.state == gh::playing) {
        //     bird.sprite.move(0, bird.speed);
        //     bird.speed += 0.5;
        // }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // close the window
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (app.state == gh::not_playing) {
                        app.state = gh::playing;
                    }
                    if (app.state == gh::playing) {
                        bird.speed = -8;
                        sound.playFly();
                    }
                } else if (event.key.code == sf::Keyboard::Escape && app.state == gh::game_over) {
                    bird.load();
                    app.score = 0;
                    // clear pipes...
                }
            }
        }

        window.clear();
        // app.drawBackground(window);
        // app.drawTitle(window);
        // app.drawGameOver(window);
        // app.drawScore(window);
        bird.draw(window);
        window.display();

        ++app.gameFrameCount;
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
        this->gameOver.setPosition(270, 200);
        this->gameOver.setScale(1.8, 1.8);

        scoreText.setFont(font);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setCharacterSize(35);
        scoreText.setString("SCORE : " + std::to_string(score));
        scoreText.setPosition(15, 10);

        highScoreText.setFont(font);
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setCharacterSize(25);
        highScoreText.setString("HIGH SCORE : " + std::to_string(highScore));
        highScoreText.setPosition(15, 60);

        startText.setFont(font);
        startText.setFillColor(sf::Color::White);
        startText.setCharacterSize(35);
        startText.setString("Press SPACE to play.");
        startText.setPosition(270, 240);
    }

    void Game::drawBackground(sf::RenderWindow& window) {
        for (int i = 0; i < 3; ++i) {
            window.draw(this->background[i]);
        }
    }

    void Game::drawTitle(sf::RenderWindow& window) { window.draw(this->title); }

    void Game::drawGameOver(sf::RenderWindow& window) { window.draw(this->gameOver); }

    void Game::drawScore(sf::RenderWindow& window) {
        window.draw(scoreText);
        window.draw(highScoreText);
        window.draw(startText);
    }

}  // namespace gh
